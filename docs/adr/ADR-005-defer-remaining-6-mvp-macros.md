# ADR-005: Deferral of 6 MVP Target Macros

**Date**: 2026-02-22  
**Status**: Superseded (by P6.1 Macro-10 Expansion)  
**Context**:  
The `P6 Alignment Audit (F-P6A-004)` identified a macro target drift: project knowledge documents (such as `techstack.docx` and `supplementarna_specifikacija.docx`) describe an MVP target of 10 core macros. However, the current backend implementation, specifically `docs/spec/p1_schema_freeze.md`, only defines 4 active macros (`macro.neuro_formant`, `macro.fm_metal`, `macro.roller_dynamics`, `macro.liquid_depth`). 

The remaining 6 macros are heavily hinted at in the modulation matrix examples (e.g., LFO mappings to Sub Volume, Character Filter Cutoff, Wavefold Threshold, Wavetable Position, FM Depth, and OTT Depth), but they lack explicitly documented names, canonical IDs, and UX behavior logic.

**Decision**:  
Following "Path B" of the F-P6A-004 remediation options, we formally **deferred** the implementation of the remaining 6 macros. The active MVP macro contract consists of exactly the 4 implemented macros.

**Update (P6.1)**:
The initial decision to defer these 6 macros was reversed in Phase 6.1 (Macro-10 Expansion) to align with the frontend team's needs and fulfill the original 10-macro product spec. All 10 macros are now actively integrated in the domain and DSP backend.

**Consequences**:  
- Historical only: explains why temporary defer happened during P6 alignment.
- Active contract moved to Macro-10 implementation in P6.1.
- `docs/spec/mvp_macro_contract.md` and `docs/spec/macro_10_contract_proposal.md` are now authoritative for runtime macro scope.
