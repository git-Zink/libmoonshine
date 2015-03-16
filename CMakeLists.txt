cmake_minimum_required (VERSION 2.8)

set (LIB_NAME "moonsine")
set (TEST_NAME "moonshine_test")

file (GLOB_RECURSE LIB_SRCS "./src/*.cpp")
file (GLOB_RECURSE TEST_SRCS "./test/*.cpp")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(${TEST_NAME} "./src")

add_library (${LIB_NAME} SHARED ${LIB_SRCS})
add_executable (${TEST_NAME} ${TEST_SRCS})

target_link_libraries (${TEST_NAME} ${LIB_NAME})
