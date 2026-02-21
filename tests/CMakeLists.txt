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
