# Backend/DSP P1 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P1 remediation patch-set prema orchestrator reviewu i schema freeze dokumentu.

OBAVEZNO PROČITAJ:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_p1_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_p1_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md

OBAVEZNE IZMJENE U P1:
1) Uskladi style set na MVP frozen set: Tech/Neuro/Dark.
2) Uskladi FM ratio curated set prema docs/spec/p1_schema_freeze.md.
3) Uskladi macro ID naming na canonical format, uključujući `macro.roller_dynamics`.
4) Razjasni i dokumentiraj unit semantiku `RawInputParams` (što je normalized, što je ms).
5) `macroRollerDyn` ili implementiraj kroz ConstraintEngine ili eksplicitno deferaj uz TODO + razlog.
6) Ako ostaje Catch2 preko FetchContent, dodaj kratku ADR napomenu i plan.

OGRANIČENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P1_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - kako je svaki finding iz backend/frontend reviewa zatvoren
3) Nemoj prelaziti na P2 bez potvrde orkestratora.
```
