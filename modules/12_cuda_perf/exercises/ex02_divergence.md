# ex02_divergence – Branch divergence experiment

What you are building: Kernel branch on idx%2 and measurement of slowdown.
Why it matters: Demonstrates warp divergence costs.

Prerequisites check
- CUDA build ready.

Files you will touch
- `src/cuda/cuda_stage.cu` (add optional divergent kernel behind flag)
- `modules/12_cuda_perf/artifacts/ex02_metrics.txt`

Steps
1. Add divergent path controlled by env var or flag; measure runtime using cudaEvent timing.
2. Run benchmark twice (divergent vs normal) and record metrics to artifacts file.

Verification
- Divergent version slower; metrics documented.

Stop here and commit
- Message: "Module12: divergence study"

If it fails
- Kernel launch fails: check grid/block sizes >0.
