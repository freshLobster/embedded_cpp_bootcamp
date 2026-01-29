
# Self-review checklist - Concurrency
- [ ] Code matches `STYLE.md` conventions (naming, RAII, no raw new/delete).
- [ ] Headers minimal includes; compilation warnings = 0.
- [ ] Concurrency: no detached threads; uses stop tokens where applicable.
- [ ] Logging: no stray `std::cout`; use logging helpers.
- [ ] Tests: clear assertions and deterministic expectations.
