# Module 04_architecture - Architecture

**Mission:** Pipeline topology, interfaces, tracing, backpressure.

**Estimated time:** 2-4 hours.

## Setup checklist (WSL2 primary, Windows notes)
- WSL2 Ubuntu: `sudo apt-get update && sudo apt-get install -y build-essential cmake ninja-build git python3 python3-venv clang clang-format clang-tidy gdb`
- Verify compiler: `clang++ --version` (expect version output). On Windows native: open "x64 Native Tools" and run `cl /?`.
- Repo root contains `CMakePresets.json` and `tools/grader/grade.py`.
## Lecture

### Topic contracts and interface topology
ROS 2 topics are a primary interface style for continuous data streams like sensor data and robot state, and they are built on a publish/subscribe model. Producers and consumers meet via a shared topic name, and data published to that topic is delivered to all subscribers, which creates the familiar bus-like topology used in many robotics systems. That decoupling is exactly what you want in a platform core: perception stages can be swapped without rewriting controllers, and diagnostics can attach without disturbing the flow. Treat topics as stable interface contracts rather than ad-hoc message dumps. ([ROS 2 Topics](https://docs.ros.org/en/humble/Concepts/Basic/About-Topics.html))

Because the publish/subscribe system is anonymous, subscribers generally do not care which publisher produced the data and can be swapped independently. This anonymity is useful in autonomy pipelines because it allows simulation or replay nodes to stand in for real sensors without changing downstream code. It also forces you to encode semantics in the message type and schema instead of coupling on implementation details. In this module you will design topic contracts that are explicit, minimal, and testable. ([ROS 2 Topics](https://docs.ros.org/en/humble/Concepts/Basic/About-Topics.html))

### QoS as part of the interface contract
In ROS 2, a QoS profile is not a tuning detail; it is part of the interface contract between publishers and subscribers. The profile defines policies like durability, reliability, queue depth, and sample history, which directly control what happens when production and consumption rates diverge. For example, "keep last" with a depth N bounds the queue, while "keep all" stores everything subject to resource limits. If you do not specify QoS explicitly, you are leaving determinism to defaults. ([ROS 2 QoS](https://docs.ros.org/en/humble/Concepts/Intermediate/About-Quality-of-Service-Settings.html))

This matters in embedded robotics because QoS choices determine whether your system prefers freshness, completeness, or robustness to loss. A best-effort reliability policy can be correct for high-rate sensors where stale data is worse than missing samples, while a reliable policy is essential for control commands that must arrive. Depth and history settings map directly to bounded-buffer behavior and latency under load. The exercises in this module make you encode those choices so they can be tested and reasoned about. ([ROS 2 QoS](https://docs.ros.org/en/humble/Concepts/Intermediate/About-Quality-of-Service-Settings.html))

### Tracing and backpressure for observable pipelines
Tracing turns a multi-stage pipeline into something you can measure instead of guess. OpenTelemetry defines traces as the path of a request through a system, and spans as the unit of work that make up those traces, each with timestamps and context. That model fits robotics pipelines well: a camera frame becomes a trace and each processing stage becomes a span, which lets you explain latency and jitter in concrete terms. The moment you can draw those spans, you can budget and enforce timing. ([OpenTelemetry Traces](https://opentelemetry.io/docs/concepts/signals/traces/), [OpenTelemetry Traces](https://opentelemetry.io/docs/concepts/signals/traces/))

Backpressure is the other half of a stable pipeline. The Reactive Streams specification emphasizes non-blocking backpressure and explicitly ties it to bounded queues so that fast producers cannot force unbounded buffering on consumers. It even makes queue bounds subscriber-controlled, which is the same principle behind bounded queues and demand-driven scheduling in embedded systems. If you design your pipeline edges to respect backpressure, you can keep memory bounded and latency predictable under load. ([Reactive Streams Spec](https://github.com/reactive-streams/reactive-streams-jvm#reactive-streams), [Reactive Streams](https://www.reactive-streams.org/))



## Start here
1) Pick one exercise folder below and `cd` into it.
2) Follow the exercise README exactly; it includes build/test commands and grading steps.
3) Save outputs in that exercise's `learner/artifacts/`.

## Exercises (per-folder)
| Exercise | Link |
|---|---|
| ex01_topic_contract | [ex01_topic_contract](exercises/ex01_topic_contract/README.md) |
| ex02_tracing | [ex02_tracing](exercises/ex02_tracing/README.md) |
| ex03_backpressure | [ex03_backpressure](exercises/ex03_backpressure/README.md) |

## Done definition
- Each exercise you attempt has passing tests and saved artifacts.
- The per-exercise grader reports a numeric score.
- Module-level artifacts (if any) are stored in `modules/04_architecture/artifacts/`.

## Checklists and evidence
Use these files in `modules/04_architecture/checklists/`:
- `mastery.md`: confirm you can explain the module goal, list failure modes you found, and map skills to autonomy/defense use cases.
- `validation.md`: run the validation commands and record results. At minimum:
  - `cmake --preset dev`
  - `ctest --preset dev -R Module04_architecture` (if the module test filter exists)
- `review.md`: perform a quick self-review against `STYLE.md` and confirm no warnings or unsafe patterns remain.

Save any required artifacts in `modules/04_architecture/artifacts/` and in each exercise’s `learner/artifacts/` folder.

## Grade this module
- Module-level grader: `python3 tools/grader/grade.py --module modules/04_architecture`
- JSON: `python3 tools/grader/grade.py --module 04 --json`
- Per-exercise grading is done inside each exercise folder README.
