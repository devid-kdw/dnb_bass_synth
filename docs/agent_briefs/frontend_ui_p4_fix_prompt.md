# Frontend/UI P4 Fix Prompt (Copy/Paste)

```text
TI SI FRONTEND/UI AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P4 conditional sync nakon backend P4 remediation patcha.

OBAVEZNO PROCI TAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p4_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_agent_brief.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_phase_tasklist.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/frontend_ui_p4_fix_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_p4_integration_checklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P4_handoff.md
9) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P4_handoff_fix.md (ako postoji)
10) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
11) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
12) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
13) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P4 FIX-u:
1) Potvrdi da frontend i dalje ostaje:
   - macro-first
   - restriction-first
   - bez runtime UI->DSP bypassa
2) Ako backend P4 fix NIJE promijenio frontend-facing contract:
   - ne radi runtime UI wiring
   - predaj no-change handoff
3) Ako backend P4 fix JEST promijenio contract (npr. style morph state surface imena/progress):
   - napravi minimalni doc-level alignment:
     - update `docs/qa/frontend_p4_integration_checklist.md`
   - bez ulaska u P5 implementaciju

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne bypassaj domain/ConstraintEngine.
- Ne uvodi neodobrene dependencyje.
- Ne prelazi na P5 runtime wiring.

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/frontend_phase_handoffs/P4_handoff_fix.md
2) U handoffu navedi:
   - je li bilo code/doc changeova
   - changed files (ako postoje)
   - tocno sto je provjereno/uskladeno
   - potvrdu da nema bypassa i nestabilnog runtime bindinga
3) Predlozi status samo do `Review`.
```
