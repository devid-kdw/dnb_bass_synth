# Backend/DSP P6.1 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6.1 remediation patch-set za zatvaranje nalaza iz `docs/qa/p6_1_review.md` i backend dijela P6->P7 gate odstupanja.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_1_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p6_to_p7_gate_deviations.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/macro_10_contract_proposal.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/mvp_macro_contract.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
10) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
11) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p6_1_fix_tasklist.md
12) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff.md
13) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff.md
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P6.1 FIX:
1) Zatvori `F-P6.1-001` (FM Pressure style contract drift):
   - uskladi `macro.fm_pressure` sa style cap logikom `Tech < Neuro < Dark` (ne smije biti Dark-only).
   - updateaj domain i testove da dokazu stilsku progresiju.
2) Zatvori `F-P6.1-002` (domain safety clamp drift):
   - dodaj finalni domain clamp za `filterCutoff` nakon svih macro doprinosa.
3) Zatvori `F-P6.1-004` + `G-P6P7-002` (evidence integrity):
   - ispravi `docs/qa/backend_phase_handoffs/P6_handoff.md` (tocan command: `ctest -R Preset`).
   - uskladi wording sa realnim `PresetSchema` wrapper namingom.
4) Ucvrsti `G-P6P7-003` (single source plugin version):
   - ukloni hardcoded drift rizik i izvedi `plugin_version` iz jednog source-of-truth mehanizma.
   - dodaj test koji to verificira.
5) Uskladi backend handoff packet:
   - ukloni netocne tvrdnje (npr. nerelevantan React smjer, pogresni broj testova/targeta).

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi nove dependencyje.
- Ne ulazi u P7 feature scope.
- RT-safe pravila su obavezna.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) cd build && ctest --output-on-failure -R Preset
5) U handoffu navedi closure mapu: `finding_id -> changed_file -> test_evidence`.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_1_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P6.1-001`, `F-P6.1-002`, `F-P6.1-004`, `G-P6P7-002`, `G-P6P7-003`
   - eventualni preostali rizik (ako postoji)
3) Predlozi status samo do `Review`.
```
