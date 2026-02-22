TI SI BACKEND/DSP AGENT ZA DnB Bass Synth VST3.

RADNI ROOT:
/Users/grzzi/Desktop/dnb_bass_synth

TASK: P8 backend CI/CD hardening support (zadnja faza prije final MVP release candidate-a).

OBAVEZNO PROCI OVAJ REDOSLIJED DOKUMENATA:
1) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_post_gate_daw_hotfix_review.md
2) /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/p7_final_gate_review.md
3) /Users/grzzi/Desktop/dnb_bass_synth/docs/master_implementation_plan.md
4) /Users/grzzi/Desktop/dnb_bass_synth/docs/implementation_plan.md
5) /Users/grzzi/Desktop/dnb_bass_synth/docs/project_rules.md
6) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_agent_brief.md
7) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_phase_tasklist.md
8) /Users/grzzi/Desktop/dnb_bass_synth/docs/agent_briefs/backend_dsp_p8_kickoff_tasklist.md
9) /Users/grzzi/Desktop/dnb_bass_synth/.github/workflows/ci.yml
10) /Users/grzzi/Desktop/dnb_bass_synth/.github/workflows/release.yml
11) /Users/grzzi/Desktop/dnb_bass_synth/CMakeLists.txt
12) /Users/grzzi/Desktop/dnb_bass_synth/tests/CMakeLists.txt
13) /Users/grzzi/Desktop/dnb_bass_synth/bench/CMakeLists.txt
14) /Users/grzzi/Desktop/dnb_bass_synth/tools/scripts/init_submodules.sh
15) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB Bass Synth VST Plugin Research.pdf
16) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB bass synth document for developer.pdf
17) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_Supplementarna_Specifikacija.docx
18) /Users/grzzi/Desktop/dnb_bass_synth/knowledge/DNB_Bass_VST3_TechStack_Arhitektura.docx

OBAVEZNE AKCIJE U P8:
1) Uskladi backend CI quality gates:
   - osiguraj da CI reproducibilno pokrece configure/build/ctest backend putanju.
   - pokrij backend test binarije (`domain_tests`, `engine_tests`, `dsp_tests`, `render_tests`, `preset_tests`).
2) Uskladi bench policy za CI:
   - benchmark koraci moraju imati jasan status (blocking ili non-blocking evidence) bez false-fail efekta u debug kontekstu.
3) Uskladi release workflow:
   - release artefakt korak ne smije zaobici backend quality gates.
   - checksum evidence mora biti dokumentiran za artefakt output.
4) Ne uvoditi DSP feature scope izvan P8 CI/CD hardening zadatka.

OGRANICENJA:
- Ne radi izvan root foldera.
- Ne uvodi neodobrene dependencyje.
- Ne bypassaj `domain/ConstraintEngine` granicu.
- Ne ulazi u scope izvan P8.

OBAVEZNA VERIFIKACIJA:
1) tools/scripts/init_submodules.sh
2) cmake --build build --parallel
3) cd build && ctest --output-on-failure
4) Ako diras bench CI korake:
   - cd build && ./bench/bench_voice_cpu --benchmark_min_time=0.05s --benchmark_repetitions=1
   - cd build && ./bench/bench_oversampling --benchmark_min_time=0.05s --benchmark_repetitions=1
   - cd build && ./bench/bench_macro_updates --benchmark_min_time=0.05s --benchmark_repetitions=1

OBAVEZNI OUTPUT:
1) Handoff packet u:
   /Users/grzzi/Desktop/dnb_bass_synth/docs/qa/backend_phase_handoffs/P8_handoff.md
2) U handoffu navedi:
   - changed files
   - closure map za backend P8 scope
   - tocne CI/test/bench komande + rezultati
   - measurement context (Debug/Release)
   - otvorena pitanja (ako postoje)
3) Predlozi status samo do `Review`.
