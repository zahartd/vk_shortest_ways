cmake_minimum_required(VERSION 3.16)
project(vk_shortest_ways CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(HAVE_STD_REGEX 1)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Graph.cpp
    src/FileReader.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmarks)
