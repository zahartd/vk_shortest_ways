cmake_minimum_required(VERSION 3.16)
project(VKShortestWays CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

add_executable(vk_shortest_ways_app
    src/main.cpp
    src/Graph.cpp
    src/FileReader.cpp
)
target_include_directories(vk_shortest_ways_app PUBLIC ${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
