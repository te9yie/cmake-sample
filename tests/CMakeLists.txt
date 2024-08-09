cmake_minimum_required(VERSION 3.16)
project(sample_tests)

# 
add_executable(${PROJECT_NAME}
    fizzbuzz_test.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    sample_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
