# Grader

## Run
- Grade one module by path: `python3 tools/grader/grade.py --module modules/01_foundations`
- Grade by number: `python3 tools/grader/grade.py --module 03`
- Grade all: `python3 tools/grader/grade.py --all`
- Grade one exercise: `python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard`
- Grade exercise solution: `python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --use-solution`
- Print requirements/rubric for a target: `python3 tools/grader/grade.py --exercise modules/01_foundations/exercises/ex01_scope_guard --print-requirements`
- JSON output: `python3 tools/grader/grade.py --module 01 --json`
- Enable hardware/CUDA-specific checks: add `--enable-hardware` and/or `--enable-cuda`.

## What it does
- Loads `grading/rubric.json` in each module.
- Executes checks (build/tests/artifacts/format/tools/log parsing) deterministically.
- Scores 0-100 per module, prints per-check breakdown, recommendations, runtime, and environment summary.
- Skips tool-dependent checks when tools are missing (partial credit as defined in rubric).

## Module vs Exercise grading
- **Module grading** uses `modules/NN_name/grading/rubric.json` and expects artifacts under `modules/NN_name/artifacts/`.
- **Exercise grading** uses `modules/NN_name/exercises/exXX_slug/grading/rubric.json` and targets either `learner/` (default) or `solution/` with `--use-solution`.

## Adding/Editing Rubrics
- Each module has `grading/rubric.json`. Total points must sum to 100.
- Supported check types:
  - `cmake_build` {preset}
  - `ctest` {preset, regex?}
  - `file_exists` {pattern}
  - `file_contains` {file, regex, invert?}
  - `tool_present` {name}
  - `command` {cmd: [..], regex?, timeout?}
  - `clang_format_check` {files: [...]}
  - `csv_schema` {file, headers?, min_rows?, has_header?}
  - `time_budget` {cmd: [..], seconds}
- Optional fields: `skip_if_missing_tool`, `skip_points`, `requires_flag` (`hardware`|`cuda`), `tool`.

## Expected Artifacts
- Each module's artifacts/README.md lists filenames; rubrics reference these via `file_exists` or `file_contains`.

## Notes
- Runs on WSL2/Ubuntu and Windows (degrades gracefully if Linux-only tools missing).
- Keep checks fast; heavy profiling tools should be optional and flagged.
