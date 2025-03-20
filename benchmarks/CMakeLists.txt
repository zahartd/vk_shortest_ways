include(FetchContent)
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.1.zip
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Benchmark tests" FORCE)

FetchContent_MakeAvailable(benchmark)

add_executable(${PROJECT_NAME}_benchmarks
    benchmark_graph.cpp
    ${PROJECT_SOURCE_DIR}/src/Graph.cpp
    ${PROJECT_SOURCE_DIR}/src/GraphGenerators.cpp
)
target_include_directories(${PROJECT_NAME}_benchmarks PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}_benchmarks benchmark::benchmark)

