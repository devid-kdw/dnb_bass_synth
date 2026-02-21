# ADR-003: Domain Gate as the Only DSP Input Path

- Status: Accepted
- Date: 2026-02-21

## Context
Project rules define strict architecture boundaries: `app/ui -> domain/ConstraintEngine -> engine -> dsp`. DnB safety limits (phase lock, crossover policy, FM ratio curation, macro mapping) must have one authoritative enforcement layer.

## Decision
Keep `domain/ConstraintEngine` as the only sanctioned parameter path into DSP/engine processing, with no direct UI/APVTS bypass into `src/dsp/`.

## Alternatives
1. Direct parameter reads from UI/APVTS inside DSP modules.
2. Duplicate partial constraint logic in both UI and DSP layers.
3. Route some parameters through domain and some directly to DSP for performance shortcuts.

## Consequences
1. Positive: deterministic enforcement of DnB constraints and fewer regression vectors.
2. Positive: simpler testability because constraint behavior is centralized.
3. Negative: extra translation layer that must be maintained when schema evolves.
4. Follow-up: architecture reviews must reject any bypass that skips domain sanitization.
