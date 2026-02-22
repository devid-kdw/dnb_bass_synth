TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P7 remediation patch-set za zatvaranje nalaza `F-P7R-003` i `F-P7R-004` prije P8 gate-a.

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_fix_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p7_fix_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P7_qa_handoff.md
9) /Users/grzzi/Desktop/dnb_bass_synth/tests/render/test_aliasing.cpp
10) /Users/grzzi/Desktop/dnb_bass_synth/tests/render/test_qa_scenarios.cpp
11) /Users/grzzi/Desktop/dnb_bass_synth/bench/bench_voice_cpu.cpp
12) /Users/grzzi/Desktop/dnb_bass_synth/bench/bench_oversampling.cpp
13) /Users/grzzi/Desktop/dnb_bass_synth/bench/bench_macro_updates.cpp
14) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE IZMJENE:
1) Zatvori `F-P7R-003` (aliasing QA evidence gap):
   - Nadogradi `tests/render/test_aliasing.cpp` tako da mjeri aliasing-orijentirani signalni kriterij (ne samo NaN/Inf + peak).
   - Uskladi naziv testa, komentare i threshold s realnim metrikama.
   - Odrzi test deterministickim i CI-stabilnim.
2) Zatvori `F-P7R-004` (handoff evidence drift):
   - Re-runaj bench i test komande, navedi tocne rezultate.
   - Ispravi backend P7 handoff da bude evidence-backed i reproduktibilan.
3) Ne uvoditi P8 scope.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne bypassaj `domain/ConstraintEngine` granicu.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Bench verifikacija (s vremenskim suffixom):
   - ./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1
   - ./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1
   - ./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P7_qa_handoff_fix.md
2) U handoffu navedi:
   - changed files
   - closure map za `F-P7R-003`, `F-P7R-004`
   - tocne test i bench komande + rezultati
   - measurement context (Debug/Release)
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
