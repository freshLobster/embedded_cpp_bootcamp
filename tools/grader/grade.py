#!/usr/bin/env python3
"""
Deterministic module grader.
- Supports per-module rubrics in modules/<module>/grading/rubric.json
- Check types: cmake_build, ctest, file_exists, file_contains, tool_present,
  command, clang_format_check, csv_schema, time_budget.
- Skips tools gracefully with partial credit when configured.
"""

import argparse
import csv
import json
import os
import platform
import re
import shutil
import subprocess
import sys
import time
from glob import glob
from typing import Any, Dict, List, Tuple


def is_wsl() -> bool:
    try:
        with open("/proc/version", "r", encoding="utf-8") as f:
            return "microsoft" in f.read().lower()
    except OSError:
        return False


def run_cmd(cmd: List[str], timeout: int = 120) -> Tuple[int, str, str, float]:
    start = time.time()
    try:
        p = subprocess.run(
            cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=timeout, text=True, check=False
        )
        return p.returncode, p.stdout, p.stderr, time.time() - start
    except subprocess.TimeoutExpired as e:
        return 124, e.stdout or "", e.stderr or "timeout", time.time() - start


def check_tool(name: str) -> bool:
    return shutil.which(name) is not None


def load_rubric(path: str) -> Dict[str, Any]:
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def grade_check(check: Dict[str, Any], module_path: str, args) -> Dict[str, Any]:
    ctype = check["type"]
    points = check["points"]
    skip_points = check.get("skip_points", 0)
    requires_flag = check.get("requires_flag")
    if requires_flag == "hardware" and not args.enable_hardware:
        return {"status": "skipped", "earned": skip_points, "message": "hardware flag not enabled"}
    if requires_flag == "cuda" and not args.enable_cuda:
        return {"status": "skipped", "earned": skip_points, "message": "cuda flag not enabled"}

    tool = check.get("tool")
    if tool and not check_tool(tool):
        if check.get("skip_if_missing_tool", False):
            return {
                "status": "skipped",
                "earned": skip_points,
                "message": f"tool {tool} missing",
            }
        return {"status": "fail", "earned": 0, "message": f"tool {tool} missing"}

    try:
        if ctype == "cmake_build":
            preset = check["preset"]
            rc, out, err, dur = run_cmd(["cmake", "--preset", preset])
            if rc != 0:
                return {"status": "fail", "earned": 0, "message": f"cmake preset {preset} failed: {err.strip()}"}
            rc, out, err, dur = run_cmd(["cmake", "--build", "--preset", preset])
            if rc == 0:
                return {"status": "pass", "earned": points, "message": f"build ok ({dur:.1f}s)"}
            return {"status": "fail", "earned": 0, "message": f"build failed: {err.strip()}"}

        if ctype == "ctest":
            preset = check["preset"]
            regex = check.get("regex")
            cmd = ["ctest", "--preset", preset, "--output-on-failure"]
            if regex:
                cmd.extend(["-R", regex])
            rc, out, err, dur = run_cmd(cmd)
            status = "pass" if rc == 0 else "fail"
            msg = err.strip() if rc != 0 else f"{regex or 'all'} passed"
            return {"status": status, "earned": points if rc == 0 else 0, "message": msg}

        if ctype == "file_exists":
            pattern = os.path.join(module_path, check["pattern"])
            matches = glob(pattern)
            if matches:
                return {"status": "pass", "earned": points, "message": f"found {len(matches)} files"}
            return {"status": "fail", "earned": 0, "message": f"missing pattern {check['pattern']}"}

        if ctype == "file_contains":
            target = os.path.join(module_path, check["file"])
            if not os.path.exists(target):
                return {"status": "fail", "earned": 0, "message": f"{check['file']} missing"}
            with open(target, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()
            pattern = re.compile(check["regex"], re.MULTILINE)
            invert = check.get("invert", False)
            found = bool(pattern.search(content))
            ok = (not invert and found) or (invert and not found)
            status = "pass" if ok else "fail"
            return {
                "status": status,
                "earned": points if ok else 0,
                "message": ("match" if found else "no match") + f" / regex {check['regex']}",
            }

        if ctype == "tool_present":
            present = check_tool(check["name"])
            status = "pass" if present else "fail"
            return {"status": status, "earned": points if present else 0, "message": f"{check['name']} {'ok' if present else 'missing'}"}

        if ctype == "command":
            cmd = check["cmd"]
            rc, out, err, dur = run_cmd(cmd, timeout=check.get("timeout", 120))
            if rc != 0:
                return {"status": "fail", "earned": 0, "message": f"rc={rc} stderr={err.strip()}"}
            regex = check.get("regex")
            if regex:
                if not re.search(regex, out + err, re.MULTILINE):
                    return {"status": "fail", "earned": 0, "message": f"output missing {regex}"}
            return {"status": "pass", "earned": points, "message": f"rc=0 ({dur:.1f}s)"}

        if ctype == "clang_format_check":
            files = [os.path.join(module_path, f) for f in check["files"]]
            cmd = ["clang-format", "--dry-run", "-Werror"] + files
            rc, out, err, dur = run_cmd(cmd, timeout=60)
            if rc == 0:
                return {"status": "pass", "earned": points, "message": "clang-format clean"}
            return {"status": "fail", "earned": 0, "message": err.strip() or out.strip()}

        if ctype == "csv_schema":
            target = os.path.join(module_path, check["file"])
            if not os.path.exists(target):
                return {"status": "fail", "earned": 0, "message": "csv missing"}
            min_rows = check.get("min_rows", 1)
            headers = check.get("headers")
            has_header = check.get("has_header", True)
            rows = []
            with open(target, newline="", encoding="utf-8", errors="ignore") as f:
                reader = csv.reader(f)
                for r in reader:
                    rows.append(r)
            if has_header:
                if not rows:
                    return {"status": "fail", "earned": 0, "message": "csv empty"}
                if headers and rows[0] != headers:
                    return {"status": "fail", "earned": 0, "message": f"header mismatch {rows[0]} vs {headers}"}
                data_rows = rows[1:]
            else:
                data_rows = rows
            if len(data_rows) < min_rows:
                return {"status": "fail", "earned": 0, "message": f"rows {len(data_rows)} < {min_rows}"}
            return {"status": "pass", "earned": points, "message": f"rows {len(data_rows)}"}

        if ctype == "time_budget":
            cmd = check["cmd"]
            budget = check["seconds"]
            rc, out, err, dur = run_cmd(cmd, timeout=budget + 5)
            if rc != 0:
                return {"status": "fail", "earned": 0, "message": f"rc {rc}"}
            if dur <= budget:
                return {"status": "pass", "earned": points, "message": f"{dur:.2f}s <= {budget}"}
            return {"status": "fail", "earned": 0, "message": f"{dur:.2f}s > {budget}"}

    except Exception as e:  # pylint: disable=broad-except
        return {"status": "fail", "earned": 0, "message": f"exception {e}"}

    return {"status": "fail", "earned": 0, "message": f"unknown check type {ctype}"}


def grade_module(module_path: str, args) -> Dict[str, Any]:
    rubric_path = os.path.join(module_path, "grading", "rubric.json")
    rubric = load_rubric(rubric_path)
    checks = rubric["checks"]
    total_points = sum(c["points"] for c in checks)
    earned = 0
    results = []
    start = time.time()
    for check in checks:
        res = grade_check(check, module_path, args)
        res["id"] = check["id"]
        res["description"] = check["description"]
        res["points"] = check["points"]
        results.append(res)
        earned += res["earned"]
    runtime = time.time() - start
    score = round((earned / total_points) * 100, 1) if total_points else 0.0
    failed = [r for r in results if r["status"] == "fail"]
    skipped = [r for r in results if r["status"] == "skipped"]
    recommendations = []
    for r in failed[:5]:
        recommendations.append(f"{r['id']}: {r['description']} -> {r['message']}")
    if not recommendations and skipped:
        for r in skipped[:5]:
            recommendations.append(f"{r['id']}: skipped ({r['message']})")

    env = {
        "platform": platform.platform(),
        "python": sys.version.split()[0],
        "wsl": is_wsl(),
        "tools": {t: check_tool(t) for t in ["clang-format", "cmake", "ctest", "perf", "heaptrack", "nsys", "nvidia-smi"]},
    }
    return {
        "module": os.path.basename(module_path),
        "score": score,
        "earned": earned,
        "possible": total_points,
        "results": results,
        "recommendations": recommendations,
        "runtime_sec": round(runtime, 2),
        "env": env,
    }


def discover_modules(root: str) -> List[str]:
    mods = []
    for entry in sorted(os.listdir(root)):
        mpath = os.path.join(root, entry)
        if os.path.isdir(mpath) and os.path.exists(os.path.join(mpath, "grading", "rubric.json")):
            mods.append(mpath)
    return mods


def main():
    parser = argparse.ArgumentParser(description="Module grader")
    parser.add_argument("--module", help="path or module id (e.g., modules/01_foundations or 01)")
    parser.add_argument("--all", action="store_true", help="grade all modules")
    parser.add_argument("--json", action="store_true", help="machine-readable JSON output")
    parser.add_argument("--enable-hardware", action="store_true", help="enable hardware-required checks")
    parser.add_argument("--enable-cuda", action="store_true", help="enable cuda-required checks")
    args = parser.parse_args()

    root = os.path.join(os.getcwd(), "modules")
    modules = []
    if args.all or (args.module is None):
        modules = discover_modules(root)
    else:
        if os.path.isdir(args.module):
            modules = [args.module]
        else:
            # try match by prefix number
            for m in discover_modules(root):
                if os.path.basename(m).startswith(args.module):
                    modules = [m]
                    break
        if not modules:
            print(f"Module {args.module} not found", file=sys.stderr)
            sys.exit(1)

    all_results = []
    for m in modules:
        res = grade_module(m, args)
        all_results.append(res)

    if args.json:
        print(json.dumps(all_results, indent=2))
        return

    for res in all_results:
        print(f"== {res['module']} : {res['score']} ({res['earned']}/{res['possible']}) runtime {res['runtime_sec']}s")
        for r in res["results"]:
            print(f"  [{r['status']}] {r['id']} ({r['earned']}/{r['points']}) - {r['description']} :: {r['message']}")
        if res["recommendations"]:
            print("  Recommendations:")
            for rec in res["recommendations"]:
                print(f"   - {rec}")
        print("")

    overall = sum(r["score"] for r in all_results) / len(all_results) if all_results else 0
    print(f"Overall score: {overall:.1f} across {len(all_results)} modules")


if __name__ == "__main__":
    main()
