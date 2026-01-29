# ex01_topic_contract – Document bus topics

What you are building: Formal topic contract doc and hook into repo docs.
Why it matters: Clear schemas prevent integration bugs between perception/control.

Prerequisites check
- `ls docs/topic_contract.md`

Files you will touch
- `docs/topic_contract.md`
- `modules/04_architecture/artifacts/ex01_topic_contract.txt`

Steps
1. Open existing doc and expand with rate/units/ownership for all topics used in pipeline.
2. Add new topic `health.heartbeat` with payload `iso_timestamp` and rate 1 Hz.
3. Save updated doc and copy a summary into artifacts:
```
grep -n "health.heartbeat" docs/topic_contract.md > modules/04_architecture/artifacts/ex01_topic_contract.txt
```
Expected: entry present.

Verification
- Doc contains new topic and rates.
- `ctest --preset dev` still passes (doc change only).

Stop here and commit
- Message: "Module04: extend topic contract"

If it fails
- Missing file: ensure repo up to date.

Stretch goals
- Add versioning field to payloads.
