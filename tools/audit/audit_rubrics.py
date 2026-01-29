#!/usr/bin/env python3
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ALLOWED_TYPES = {
    "command",
    "cmake_build",
    "ctest",
    "file_exists",
    "file_contains",
    "tool_present",
    "clang_format_check",
    "csv_schema",
    "time_budget",
}


def main() -> int:
    failures = []
    rubric_files = list(ROOT.rglob("rubric.json"))
    for rf in rubric_files:
        data = json.loads(rf.read_text(encoding="utf-8"))
        checks = data.get("checks", [])
        total = sum(c.get("points", 0) for c in checks)
        if total != 100:
            failures.append(f"{rf.relative_to(ROOT)} points={total}")
        for c in checks:
            if c.get("type") not in ALLOWED_TYPES:
                failures.append(f"{rf.relative_to(ROOT)} unknown type {c.get('type')}")
            if c.get("type") == "tool_present" and not c.get("skip_if_missing_tool", False):
                # warn if missing skip policy
                pass

    if failures:
        print("Rubric issues:")
        for f in failures:
            print("  -", f)
        return 2
    print("OK: rubrics valid and sum to 100")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
