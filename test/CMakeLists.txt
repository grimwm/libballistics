cmake_minimum_required(VERSION 3.1)

find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests
        pbr_check.cpp)

target_link_libraries(runTests gtest gtest_main pthread)
target_link_libraries(runTests ballistics)