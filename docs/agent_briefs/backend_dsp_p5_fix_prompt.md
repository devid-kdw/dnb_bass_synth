# Backend/DSP P5 Fix Prompt (Copy/Paste)

```text
TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P5 remediation patch-set za zatvaranje review findings (`F-P5-001`, `F-P5-002`, `F-P5-003`, `F-P5-004`).

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p5_fix_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/P5_handoff.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff.md
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE U P5:
1) Zatvori `F-P5-001` (style.mode contract gap):
   - Implementiraj canonical param ID `style.mode` u aktivnom APVTS layoutu.
   - Osiguraj deterministic mapiranje APVTS -> `RawInputParams.activeStyle` (Tech/Neuro/Dark).
   - Nema bypassa `domain/ConstraintEngine`.
2) Zatvori `F-P5-002` (style morph runtime effect):
   - `macro.style_morph` mora imati dokaziv utjecaj na audio path (ne samo internal state varijablu).
   - Utjecaj mora biti deterministic i testiran, bez rusenja sub-safety policy.
3) Zatvori `F-P5-003` (APVTS contract completeness):
   - Ne smije ostati dead/no-op host param u aktivnom P5 contractu.
   - Svaki exposed param mora biti:
     a) wirean kroz domain-odobren path do runtime ponasanja, ili
     b) eksplicitno deferan/uklonjen iz aktivnog layouta uz dokumentiran razlog i contract update.
4) Zatvori `F-P5-004` (handoff discipline):
   - Predaj backend P5 fix handoff u QA putanju (ne u `docs/agent_briefs/`).

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi nove dependencyje.
- Ne bypassaj domain/ConstraintEngine granicu.
- Ne ulazi u P6/P7 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Dodaj/pokreni testove koji eksplicitno dokazuju:
   - style mode mapiranje na domain behavior
   - style morph razliku u render outputu (npr. morph=0.0 vs morph=1.0 pod istim ostalim inputom)
5) Po potrebi kratki compile smoke za P5 include path:
   - `src/app/PluginProcessor.h`
   - `src/domain/ConstraintEngine.h`
   - `src/engine/SynthEngine.h`

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P5_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - test komande + rezultat
   - closure map za `F-P5-001`, `F-P5-002`, `F-P5-003`, `F-P5-004`
   - popis aktivnih APVTS parametara i status (wired/deferred)
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review` (ne `Done`).
```
