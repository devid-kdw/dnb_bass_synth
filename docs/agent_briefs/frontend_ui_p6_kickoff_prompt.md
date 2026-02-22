# Frontend/UI P6 Kickoff Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P6 frontend support sync za Preset/State/Migration nakon backend P6 contracta.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/spec/p1_schema_freeze.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p5_round3_review.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P5_handoff_fix_round3.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P6_handoff.md (ako postoji)
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P6:
1) Uskladi frontend preset/state UX s backend P6 contractom:
   - koristi samo stabilne canonical `param_id` vrijednosti
   - ne uvodi local UI state logiku koja zaobilazi backend migration pravila
2) Frontend support scope:
   - pripremi ili uskladi preset load/save UI tok (ako postoji surface u app layeru)
   - osiguraj UX fallback poruku/ponasanje za unknown/legacy state slucajeve
3) Potvrdi da nema regressije na P5 contract:
   - macro-first ostaje primaran
   - style naming ostaje `Tech/Neuro/Dark`
   - nema runtime UI->DSP bypassa
4) Ako backend P6 handoff jos ne postoji:
   - radi samo prep/doc-level alignment bez runtime binding pretpostavki
   - predaj no-change ili doc-only handoff

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj `domain/ConstraintEngine`.
- Ne uvodi neodobrene dependencyje.
- Ne ulazi u P7/P8 scope.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) U handoffu navedi binding mapu za sve UI kontrole koje diras (`ui_control -> param_id -> exists_in_apvts`).

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P6_handoff.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - tocno sto je uskladjeno s backend P6 contractom
   - potvrdu da nema runtime bypassa i nestabilnog bindinga
3) Predlozi status samo do `Review`.
```
