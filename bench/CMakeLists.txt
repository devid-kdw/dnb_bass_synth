cmake_minimum_required(VERSION 3.24)

if(NOT TARGET benchmark::benchmark)
  message(STATUS "Bench wiring enabled, but benchmark target is unavailable. Initialize extern/benchmark to activate bench targets.")
  return()
endif()

add_executable(bench_smoke bench_smoke.cpp)
target_link_libraries(bench_smoke PRIVATE benchmark::benchmark)
