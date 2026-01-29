#!/usr/bin/env python3
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MODULES = ROOT / "modules"

required_module_files = [
    "README.md",
    "overview.md",
    "troubleshooting.md",
    "references.md",
    "artifacts/README.md",
    "checklists/mastery.md",
    "checklists/validation.md",
    "checklists/review.md",
]

required_exercise_files = [
    "README.md",
    "troubleshooting.md",
    "references.md",
    "learner/CMakeLists.txt",
    "learner/include",
    "learner/src",
    "learner/tests",
    "learner/artifacts",
    "solution/CMakeLists.txt",
    "solution/include",
    "solution/src",
    "solution/tests",
    "solution/artifacts",
    "grading/rubric.json",
    "grading/expected",
    "grading/checks",
]


def check_exists(base: Path, rel: str) -> bool:
    p = base / rel
    return p.exists()


def main() -> int:
    if not MODULES.exists():
        print("modules/ missing")
        return 1

    modules = sorted([d for d in MODULES.iterdir() if d.is_dir()])
    print("Modules:", len(modules))
    failures = []

    for m in modules:
        print(f"- {m.name}")
        for req in required_module_files:
            if not check_exists(m, req):
                failures.append(f"{m.name} missing {req}")

        exroot = m / "exercises"
        if not exroot.exists():
            failures.append(f"{m.name} missing exercises/")
            continue

        exercises = sorted([d for d in exroot.iterdir() if d.is_dir()])
        print(f"  exercises: {len(exercises)}")
        for ex in exercises:
            for req in required_exercise_files:
                if not check_exists(ex, req):
                    failures.append(f"{m.name}/{ex.name} missing {req}")

    if failures:
        print("\nMissing items:")
        for f in failures:
            print("  -", f)
        return 2

    print("OK: all required module/exercise files present")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
