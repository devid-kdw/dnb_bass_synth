# ADR-001: JUCE 8 vs Alternatives

- Status: Accepted
- Date: 2026-02-21

## Context
The tech stack architecture requires a plugin-first baseline with VST3 delivery, CMake support, MIDI handling, and a maintainable path toward AU/CLAP in later phases. The project is C++20-only at runtime and must keep integration risk low while core DSP phases continue.

## Decision
Use JUCE 8 as the primary plugin framework, integrated through `extern/juce` in a submodule-first dependency model.

## Alternatives
1. iPlug2: viable but requires more custom wiring for state, GUI, and host integration.
2. DPF: lean and fast, but lacks JUCE-equivalent breadth for this project baseline.
3. Custom wrapper around raw SDKs: highest flexibility but highest implementation and maintenance risk.

## Consequences
1. Positive: faster and safer plugin target bring-up with mature host integration.
2. Positive: consistent CMake workflow across local and CI builds.
3. Negative: larger framework footprint than minimal alternatives.
4. Follow-up: pin JUCE in `.gitmodules` and use `tools/scripts/init_submodules.sh` for reproducible bootstrap.
