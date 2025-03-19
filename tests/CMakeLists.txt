include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests_app
    test_graph.cpp
    ${PROJECT_SOURCE_DIR}/src/Graph.cpp
    ${PROJECT_SOURCE_DIR}/src/FileReader.cpp
)
target_include_directories(tests_app PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tests_app gtest_main)

include(GoogleTest)
gtest_discover_tests(tests_app)
