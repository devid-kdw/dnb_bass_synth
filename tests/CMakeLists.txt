cmake_minimum_required(VERSION 3.24)

set(DNB_CATCH2_SUBMODULE_DIR "${CMAKE_SOURCE_DIR}/extern/catch2")
set(DNB_CATCH2_BOOTSTRAP_DIR "${CMAKE_BINARY_DIR}/_deps/catch2-src")
option(
  DNB_ENABLE_TESTS_CATCH2_BINARY_DIR_FALLBACK
  "Enable legacy Catch2 fallback from ${DNB_CATCH2_BOOTSTRAP_DIR} (compatibility only)."
  OFF
)

if(NOT TARGET Catch2::Catch2WithMain)
  if(EXISTS "${DNB_CATCH2_SUBMODULE_DIR}/CMakeLists.txt")
    add_subdirectory(
      "${DNB_CATCH2_SUBMODULE_DIR}"
      "${CMAKE_BINARY_DIR}/extern/catch2"
      EXCLUDE_FROM_ALL
    )
    set(DNB_CATCH2_EXTRAS_DIR "${DNB_CATCH2_SUBMODULE_DIR}/extras")
  elseif(DNB_ENABLE_TESTS_CATCH2_BINARY_DIR_FALLBACK)
    if(EXISTS "${DNB_CATCH2_BOOTSTRAP_DIR}/CMakeLists.txt")
      message(WARNING
        "Using compatibility fallback for Catch2 from ${DNB_CATCH2_BOOTSTRAP_DIR}. "
        "Default policy is strict submodule-first via extern/catch2."
      )
      add_subdirectory(
        "${DNB_CATCH2_BOOTSTRAP_DIR}"
        "${CMAKE_BINARY_DIR}/_deps/catch2-fallback"
        EXCLUDE_FROM_ALL
      )
      set(DNB_CATCH2_EXTRAS_DIR "${DNB_CATCH2_BOOTSTRAP_DIR}/extras")
    else()
      message(FATAL_ERROR
        "DNB_ENABLE_TESTS_CATCH2_BINARY_DIR_FALLBACK=ON, but fallback source is missing at "
        "${DNB_CATCH2_BOOTSTRAP_DIR}."
      )
    endif()
  else()
    message(FATAL_ERROR
      "Catch2 dependency is missing. Strict mode requires extern/catch2 to be initialized "
      "via tools/scripts/init_submodules.sh."
    )
  endif()
endif()

add_executable(domain_tests
    unit/test_parameter_ranges.cpp
    unit/test_macro_constraints.cpp
    unit/test_p5_round2.cpp
    unit/test_style_modes.cpp
    ../src/domain/ConstraintEngine.cpp
)

target_include_directories(domain_tests PRIVATE ../src)
target_link_libraries(domain_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
if(DEFINED DNB_CATCH2_EXTRAS_DIR AND EXISTS "${DNB_CATCH2_EXTRAS_DIR}/Catch.cmake")
  include("${DNB_CATCH2_EXTRAS_DIR}/Catch.cmake")
else()
  include(Catch)
endif()
catch_discover_tests(domain_tests)

add_executable(engine_tests
    engine/test_note_stack.cpp
    engine/test_voice_allocator.cpp
    engine/test_regression.cpp
    engine/test_p5_round3.cpp
    ../src/domain/ConstraintEngine.cpp
)
target_include_directories(engine_tests PRIVATE ../src)
target_link_libraries(engine_tests PRIVATE Catch2::Catch2WithMain)

if(DEFINED DNB_CATCH2_EXTRAS_DIR AND EXISTS "${DNB_CATCH2_EXTRAS_DIR}/Catch.cmake")
  include("${DNB_CATCH2_EXTRAS_DIR}/Catch.cmake")
else()
  include(Catch)
endif()
catch_discover_tests(engine_tests)

add_executable(dsp_tests
    dsp/test_anti_click.cpp
    dsp/test_dc_blocker.cpp
    dsp/test_oversampler.cpp
    dsp/test_smoother.cpp
    dsp/test_denormal_flush.cpp
    dsp/test_sanity_check.cpp
    dsp/test_sub_phase_lock.cpp
    dsp/test_character_osc.cpp
    dsp/test_crossover_lr4.cpp
    dsp/test_state_variable_filter.cpp
    dsp/test_saturator.cpp
    dsp/test_wavefolder.cpp
)

target_include_directories(dsp_tests PRIVATE ../src)
target_link_libraries(dsp_tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(dsp_tests)

add_executable(render_tests
    render/test_aliasing.cpp
    render/test_qa_scenarios.cpp
    ../src/domain/ConstraintEngine.cpp
)

target_include_directories(render_tests PRIVATE ../src)
target_link_libraries(render_tests PRIVATE Catch2::Catch2WithMain juce::juce_audio_processors juce::juce_dsp spdlog::spdlog)
catch_discover_tests(render_tests)

if(TARGET juce::juce_audio_processors)
add_executable(preset_tests
    unit/test_preset_manager.cpp
    ../src/preset/PresetManager.cpp
    ../src/preset/PresetMigration.cpp
)

target_include_directories(preset_tests PRIVATE ../src)
target_link_libraries(preset_tests PRIVATE 
    Catch2::Catch2WithMain 
    nlohmann_json::nlohmann_json
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_data_structures)
catch_discover_tests(preset_tests)
endif()
