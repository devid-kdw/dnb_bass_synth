cmake_minimum_required(VERSION 3.24)

if(NOT TARGET benchmark::benchmark)
  message(STATUS "Bench wiring enabled, but benchmark target is unavailable. Initialize extern/benchmark to activate bench targets.")
  return()
endif()

add_executable(bench_smoke bench_smoke.cpp)
target_link_libraries(bench_smoke PRIVATE benchmark::benchmark)

add_executable(bench_voice_cpu bench_voice_cpu.cpp ../src/domain/ConstraintEngine.cpp)
target_include_directories(bench_voice_cpu PRIVATE ../src)
target_link_libraries(bench_voice_cpu PRIVATE benchmark::benchmark juce::juce_audio_processors juce::juce_dsp spdlog::spdlog)

add_executable(bench_oversampling bench_oversampling.cpp)
target_include_directories(bench_oversampling PRIVATE ../src)
target_link_libraries(bench_oversampling PRIVATE benchmark::benchmark juce::juce_audio_processors juce::juce_dsp)

add_executable(bench_macro_updates bench_macro_updates.cpp ../src/domain/ConstraintEngine.cpp)
target_include_directories(bench_macro_updates PRIVATE ../src)
target_link_libraries(bench_macro_updates PRIVATE benchmark::benchmark juce::juce_audio_processors juce::juce_dsp)
