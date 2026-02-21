cmake_minimum_required(VERSION 3.24)
project(DnBBassSynth VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DNB_ENABLE_PLUGIN_TARGET "Enable JUCE plugin target wiring when extern/juce is available." ON)
option(DNB_BUILD_TESTS "Build Catch2-based test targets." ON)
option(DNB_BUILD_BENCH "Build benchmark targets." ON)

set(DNB_EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")
set(DNB_HAS_JUCE OFF)
set(DNB_HAS_BENCHMARK OFF)
set(DNB_HAS_SPDLOG OFF)
set(DNB_HAS_HIIR OFF)

if(EXISTS "${DNB_EXTERN_DIR}/juce/CMakeLists.txt")
  set(DNB_HAS_JUCE ON)
  add_subdirectory("${DNB_EXTERN_DIR}/juce" EXCLUDE_FROM_ALL)
endif()

if(EXISTS "${DNB_EXTERN_DIR}/benchmark/CMakeLists.txt")
  # Benchmark is used for project benches only; disable its internal gtest suite.
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
  set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "" FORCE)
  set(DNB_HAS_BENCHMARK ON)
  add_subdirectory("${DNB_EXTERN_DIR}/benchmark" EXCLUDE_FROM_ALL)
endif()

if(EXISTS "${DNB_EXTERN_DIR}/spdlog/CMakeLists.txt")
  set(DNB_HAS_SPDLOG ON)
  add_subdirectory("${DNB_EXTERN_DIR}/spdlog" EXCLUDE_FROM_ALL)
endif()

if(EXISTS "${DNB_EXTERN_DIR}/hiir")
  set(DNB_HAS_HIIR ON)
endif()

if(DNB_ENABLE_PLUGIN_TARGET)
  if(DNB_HAS_JUCE)
    if(EXISTS "${CMAKE_SOURCE_DIR}/src/app/PluginProcessor.cpp"
       AND EXISTS "${CMAKE_SOURCE_DIR}/src/app/PluginEditor.cpp")
      juce_add_plugin(DnBBassSynth
        PLUGIN_MANUFACTURER_CODE Dnbs
        PLUGIN_CODE Dbs1
        FORMATS VST3
        PRODUCT_NAME "DnB Bass Synth"
        IS_SYNTH TRUE
        NEEDS_MIDI_INPUT TRUE
      )

      juce_generate_juce_header(DnBBassSynth)

      target_sources(DnBBassSynth PRIVATE
        src/app/PluginProcessor.cpp
        src/app/PluginEditor.cpp
        src/domain/ConstraintEngine.cpp
        src/ui/theme/Theme.cpp
      )

      target_include_directories(DnBBassSynth PRIVATE
        src
      )

      if(DNB_HAS_HIIR)
        target_include_directories(DnBBassSynth PRIVATE
          extern/hiir
        )
      endif()

      target_link_libraries(DnBBassSynth PRIVATE
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_gui_basics
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
      )

      if(DNB_HAS_SPDLOG)
        target_link_libraries(DnBBassSynth PRIVATE spdlog::spdlog)
      endif()

      target_compile_definitions(DnBBassSynth PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
      )
    else()
      message(STATUS "Plugin target intent active, but src/app plugin stubs are missing; skipping DnBBassSynth target.")
    endif()
  else()
    message(STATUS "Plugin target intent active, but extern/juce is not initialized. Run tools/scripts/init_submodules.sh.")
  endif()
endif()

if(DNB_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(DNB_BUILD_BENCH)
  add_subdirectory(bench)
endif()
