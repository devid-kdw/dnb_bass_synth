# ADR-002: Per-Module Oversampling

- Status: Accepted
- Date: 2026-02-21

## Context
Knowledge documents define oversampling as mandatory around nonlinear DSP blocks (FM, wavefolding, saturator path), while preserving CPU efficiency and real-time safety. A global oversampling strategy would process linear blocks unnecessarily and increase cost.

## Decision
Adopt per-module oversampling as the baseline strategy and keep HIIR as the preferred implementation dependency under `extern/hiir`.

## Alternatives
1. Global oversampling for the entire signal path.
2. No oversampling, relying only on post-filtering.
3. Hybrid global + per-module chain with user-facing global switch.

## Consequences
1. Positive: CPU budget is focused on alias-prone nonlinear modules only.
2. Positive: architecture remains aligned with DnB-specific nonlinear hotspots.
3. Negative: implementation complexity is higher than a single global switch.
4. Follow-up: maintain explicit tests/bench coverage for oversampling paths in later QA phases.
