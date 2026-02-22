cmake_minimum_required(VERSION 3.24)
project(DnBBassSynth VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Inject project version into source code
configure_file(src/Config.h.in ${CMAKE_BINARY_DIR}/Config.h @ONLY)
include_directories(${CMAKE_BINARY_DIR})

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

if(EXISTS "${DNB_EXTERN_DIR}/json/CMakeLists.txt")
  set(DNB_HAS_JSON ON)
  set(JSON_BuildTests OFF CACHE INTERNAL "")
  add_subdirectory("${DNB_EXTERN_DIR}/json" EXCLUDE_FROM_ALL)
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

      juce_add_binary_data(DnBBassSynth_UI_Assets
        HEADER_NAME "UIAssets.h"
        NAMESPACE "UIAssets"
        SOURCES
          assets/ui/runtime/p7/ui_background_root_main_base_v001.png
          assets/ui/runtime/p7/ui_background_root_noise_base_v001.png
          assets/ui/runtime/p7/ui_panel_header_titleplate_base_v001.png
          assets/ui/runtime/p7/ui_panel_macro_primary_frame_base_v001.png
          assets/ui/runtime/p7/ui_panel_macro_advanced_frame_base_v001.png
          assets/ui/runtime/p7/ui_panel_style_selector_frame_base_v001.png
          assets/ui/runtime/p7/ui_panel_style_morph_frame_base_v001.png
          assets/ui/runtime/p7/ui_panel_visual_feedback_frame_base_v001.png
          assets/ui/runtime/p7/ui_macro_knob_neuro_formant_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_neuro_formant_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_neuro_formant_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_metal_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_metal_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_metal_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_roller_dynamics_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_roller_dynamics_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_roller_dynamics_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_liquid_depth_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_liquid_depth_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_liquid_depth_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_sub_punch_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_sub_punch_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_sub_punch_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_pressure_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_pressure_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fm_pressure_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_cutoff_motion_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_cutoff_motion_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_cutoff_motion_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fold_bite_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fold_bite_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_fold_bite_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_table_drift_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_table_drift_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_table_drift_active_v001.png
          assets/ui/runtime/p7/ui_macro_knob_smash_glue_idle_v001.png
          assets/ui/runtime/p7/ui_macro_knob_smash_glue_hover_v001.png
          assets/ui/runtime/p7/ui_macro_knob_smash_glue_active_v001.png
          assets/ui/runtime/p7/ui_style_mode_tech_idle_v001.png
          assets/ui/runtime/p7/ui_style_mode_tech_selected_v001.png
          assets/ui/runtime/p7/ui_style_mode_tech_disabled_v001.png
          assets/ui/runtime/p7/ui_style_mode_neuro_idle_v001.png
          assets/ui/runtime/p7/ui_style_mode_neuro_selected_v001.png
          assets/ui/runtime/p7/ui_style_mode_neuro_disabled_v001.png
          assets/ui/runtime/p7/ui_style_mode_dark_idle_v001.png
          assets/ui/runtime/p7/ui_style_mode_dark_selected_v001.png
          assets/ui/runtime/p7/ui_style_mode_dark_disabled_v001.png
          assets/ui/runtime/p7/ui_style_morph_track_main_base_v001.png
          assets/ui/runtime/p7/ui_style_morph_thumb_main_base_v001.png
          assets/ui/runtime/p7/ui_style_morph_glow_main_active_v001.png
          assets/ui/runtime/p7/ui_visual_scope_grid_main_base_v001.png
          assets/ui/runtime/p7/ui_visual_scope_wave_overlay_base_v001.png
          assets/ui/runtime/p7/ui_visual_scope_spectrum_overlay_base_v001.png
          assets/ui/runtime/p7/ui_visual_scope_frame_glow_active_v001.png
          assets/ui/runtime/p7/ui_badge_macro_primary_base_v001.png
          assets/ui/runtime/p7/ui_badge_macro_advanced_base_v001.png
          assets/ui/runtime/p7/ui_icon_constraint_guard_on_v001.png
          assets/ui/runtime/p7/ui_icon_mono_sub_lock_on_v001.png
          assets/ui/runtime/p7/ui_icon_oversample_indicator_on_v001.png
          assets/ui/runtime/p7/ui_icon_warning_general_on_v001.png
      )

      target_sources(DnBBassSynth PRIVATE
        src/app/PluginProcessor.cpp
        src/app/PluginEditor.cpp
        src/domain/ConstraintEngine.cpp
        src/preset/PresetManager.cpp
        src/preset/PresetMigration.cpp
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
        DnBBassSynth_UI_Assets
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

      if(DNB_HAS_JSON)
        target_link_libraries(DnBBassSynth PRIVATE nlohmann_json::nlohmann_json)
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
