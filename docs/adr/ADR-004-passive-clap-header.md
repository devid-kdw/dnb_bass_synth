# ADR-004: Passive CLAP Header Baseline

- Status: Accepted
- Date: 2026-02-21

## Context
Tech stack guidance recommends keeping CLAP support ready without expanding current MVP scope beyond VST3. The project needs a low-risk future path that avoids later repo-level refactors.

## Decision
Add CLAP as a passive header dependency baseline through `extern/clap-cleveraudio` submodule, while keeping active plugin target delivery on VST3 only in the current phase.

## Alternatives
1. Ignore CLAP completely until V2/V3 and add it later.
2. Fully activate CLAP target now with parallel host QA scope.
3. Use ad-hoc copied header files instead of tracked submodule source.

## Consequences
1. Positive: future CLAP activation path is prepared with near-zero runtime impact today.
2. Positive: dependency provenance stays explicit and reproducible in repo metadata.
3. Negative: one more external module to initialize in developer bootstrap.
4. Follow-up: CLAP activation remains phase-gated and must not bypass current VST3-first delivery priorities.
