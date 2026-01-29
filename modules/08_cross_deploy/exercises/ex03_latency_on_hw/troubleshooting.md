- Build fails: ensure CMake and compiler installed.
- #error TODO present: implement exercise() in learner/src/main.cpp.
- Tests fail: ensure exercise() returns required value (42).


6) **Windows SDK libs missing**
- Symptom: `lld-link: error: could not open 'kernel32.lib'` (and other .lib files).
- Root cause: Windows SDK / MSVC toolchain not installed or not in environment.
- Fix: install Visual Studio Build Tools with C++ workload, then run builds from the "x64 Native Tools" prompt, or build in WSL2.
- Verify: `cl /?` works and CMake config succeeds.
