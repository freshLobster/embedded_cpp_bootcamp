# Module 01_foundations - Foundations

**Mission:** RAII, ownership, API hygiene, build/test baseline.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.

## Lecture

### RAII and deterministic cleanup
Resource Acquisition Is Initialization (RAII) ties a resource’s lifetime to the lifetime of an object, so acquiring the resource happens at construction and releasing it happens at destruction. This makes resource availability a class invariant and guarantees cleanup even on early returns or exceptions because destruction happens as scopes unwind. In embedded and robotics work, where you may be acquiring locks, file handles, or hardware interfaces, RAII makes “cleanup” automatic and predictable rather than relying on a fragile sequence of manual calls. ([cppreference: RAII](https://en.cppreference.com/w/cpp/language/raii))

RAII matters in practice because the language guarantees destruction order and stack unwinding, so resources are released in reverse acquisition order and failure in a constructor unwinds already‑acquired subobjects. This is the foundation for exception safety: if a subsystem throws, you still release your GPIO handle or mutex and avoid leaving the robot in a stuck or unsafe state. The RAII pattern also generalizes beyond memory—think “scope‑bound resource management” for a critical section guard, a socket, or a sensor bus lock. ([cppreference: RAII](https://en.cppreference.com/w/cpp/language/raii))

The standard library is built around RAII, which is why types like `std::vector` and `std::string` need no explicit cleanup and why wrappers like `std::lock_guard` provide safe lock/unlock behavior. In robotics pipelines, this means you can structure control loops so that acquiring a lock or a temporary hardware resource is localized to a scope and released automatically when the scope ends. This eliminates “forgotten unlock” defects that can deadlock a real‑time system under stress. ([cppreference: RAII](https://en.cppreference.com/w/cpp/language/raii))

### Ownership semantics and smart pointers
`std::unique_ptr` expresses sole ownership: it owns and manages an object and disposes of it automatically when the `unique_ptr` goes out of scope or is reset. That single‑owner model maps well to embedded components where ownership should be unambiguous—e.g., a driver instance owning its DMA buffer or a control module owning its configuration object. Using `unique_ptr` makes lifetimes explicit and prevents accidental copies that could double‑free or leak. ([cppreference: std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr))

`std::shared_ptr` expresses shared ownership: multiple owners can hold a pointer, and the object is destroyed when the last owner releases it. This is useful when you genuinely need shared lifetime, such as a shared map of calibration data across multiple processing stages. In safety‑critical code, the key is to be deliberate—shared ownership implies more complex lifetime reasoning and can obscure when resources are released. ([cppreference: std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr))

The C++ Core Guidelines recommend using smart pointers to represent ownership and prefer `unique_ptr` over `shared_ptr` unless sharing is required, because `unique_ptr` is simpler, predictable, and avoids reference‑count overhead. For embedded systems with tight CPU budgets and real‑time constraints, this guidance is more than style—it reduces hidden work on each copy and keeps ownership straightforward during incident response. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

### Rule of 0/3/5 and special member functions
The Rule of Three states that if a class needs a user‑defined destructor, copy constructor, or copy assignment operator, it almost certainly needs all three. The reason is that C++ copies and assigns objects implicitly in many contexts, so a single custom special member function can imply the others must be correct too. In embedded firmware, violating this rule often shows up as silent resource leaks or double‑frees during container reallocation or message passing. ([cppreference: Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three))

The Rule of Five extends this to move operations: if you define (or delete) a destructor, copy constructor, or copy assignment operator, the compiler won’t implicitly generate move operations, so you should define or delete all five special members when moves are desirable. This matters in modern C++ because moving is how we transfer ownership efficiently without copying resources; missing move operations can cause performance cliffs in high‑rate pipelines. ([cppreference: Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three))

The Rule of Zero is the “best default” for most types: if your class is not directly managing a resource, avoid custom destructors and copy/move operations and let the compiler do the right thing. This pushes resource management into dedicated RAII types and keeps the bulk of your codebase simple and regular, which is crucial for large robotics codebases where predictability and refactoring safety matter. ([cppreference: Rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three))

### Interface hygiene and stability
Interface design is a reliability issue, not just a style issue. The Core Guidelines advise preferring abstract classes (pure interfaces) instead of base classes that carry state, because abstract interfaces are more stable and avoid forcing all derived classes to carry data or behavior they don’t need. For autonomy stacks with long‑lived interfaces between perception, planning, and control, stability reduces integration churn and safety regressions. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Encapsulation is equally critical: minimizing exposure of members reduces unintended access and makes it easier to enforce invariants through constructors and member functions. When you expose fields publicly, you lose control of invariants and make later changes risky; in embedded code, that can translate directly into unsafe actuator commands or invalid sensor state. Keeping data private and enforcing invariants through methods is a practical way to maintain robustness. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

Finally, when you must violate a rule for performance or hardware reasons, encapsulate the violation so the unsafe details do not leak into your interface. The guidelines explicitly recommend localizing “ugly, unsafe, or error‑prone techniques” to keep interfaces simple and safe. This is how you allow a specialized driver to do something low‑level while the rest of the system stays clean and testable. ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines))

## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_scope_guard | [ex01_scope_guard](exercises/ex01_scope_guard/README.md) |
| ex02_message_bus_view | [ex02_message_bus_view](exercises/ex02_message_bus_view/README.md) |
| ex03_interface_review | [ex03_interface_review](exercises/ex03_interface_review/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/01_foundations/artifacts/`.

## Checklists and evidence
Use these files in `modules/01_foundations/checklists/`:
- `mastery.md`: confirm you can explain the module goal, list failure modes you found, and map skills to autonomy/defense use cases.
- `validation.md`: run the validation commands and record results. At minimum:
  - `cmake --preset dev`
  - `ctest --preset dev -R Module01_foundations` (if the module test filter exists)
- `review.md`: perform a quick self-review against `STYLE.md` and confirm no warnings or unsafe patterns remain.

Save any required artifacts in `modules/01_foundations/artifacts/` and in each exercise’s `learner/artifacts/` folder.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/01_foundations`
- JSON: `python3 tools/grader/grade.py --module 01 --json`
- Per-exercise grading is done inside each exercise folder README.
