# Backend/DSP P6 Alignment Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6 alignment remediation patch-set za zatvaranje nalaza `F-P6A-001`..`F-P6A-005` (backend scope).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_alignment_audit.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p6_alignment_fix_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff.md
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE:
1) Zatvori `F-P6A-001`:
   - uvedi eksplicitan JSON-backed migration sloj unutar preset/state pipeline-a (uz postojeci ValueTree tok).
2) Zatvori `F-P6A-002`:
   - dodaj plugin-version tag u serialized state i obradi load fallback za legacy state bez tog taga.
3) Zatvori `F-P6A-003`:
   - dodaj dedicated testove za unknown-field / unknown-param tolerance.
4) Zatvori `F-P6A-004` (backend dio):
   - iz knowledge dokumenata izvuci canonical MVP macro contract u `docs/spec/mvp_macro_contract.md`.
   - zatim implementiraj closure put:
     a) `Path A` (preporuceno): puni MVP macro contract, bez host-visible dead/no-op parametara, ili
     b) `Path B`: ADR-backed defer s jasnim plan/risk updateom i bez false MVP-ready tvrdnji.
5) Zatvori `F-P6A-005` (backend dio):
   - ispravi backend P6 handoff netocnosti i predaj evidence-backed fix handoff.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne bypassaj `domain/ConstraintEngine`.
- Ne ulazi u P7/P8 implementaciju.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) cd build && ctest --output-on-failure -R preset
5) U handoffu prikazi `finding_id -> closure_evidence` mapu.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P6A-001`..`F-P6A-005` (backend scope)
   - migration matricu (`from_version -> to_version -> rezultat`)
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
```

