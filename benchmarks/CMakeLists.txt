include(FetchContent)
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.1.zip
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Benchmark tests" FORCE)

FetchContent_MakeAvailable(benchmark)

add_executable(benchmark_app
    benchmark_graph.cpp
    ${PROJECT_SOURCE_DIR}/src/Graph.cpp
    ${PROJECT_SOURCE_DIR}/src/FileReader.cpp
)
target_include_directories(benchmark_app PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(benchmark_app benchmark::benchmark)

