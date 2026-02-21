cmake_minimum_required(VERSION 3.24)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(domain_tests
    unit/test_parameter_ranges.cpp
    unit/test_macro_constraints.cpp
    unit/test_style_modes.cpp
    ../src/domain/ConstraintEngine.cpp
)

target_include_directories(domain_tests PRIVATE ../src)
target_link_libraries(domain_tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(domain_tests)

add_executable(dsp_tests
    dsp/test_anti_click.cpp
    dsp/test_dc_blocker.cpp
    dsp/test_oversampler.cpp
    dsp/test_smoother.cpp
    dsp/test_denormal_flush.cpp
    dsp/test_sanity_check.cpp
)

target_include_directories(dsp_tests PRIVATE ../src)
target_link_libraries(dsp_tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(dsp_tests)
