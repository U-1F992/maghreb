cmake_minimum_required(VERSION 3.10)

project(maghreb VERSION 0.1.0)
set(CMAKE_C_STANDARD 90)

include_directories(include)
file(GLOB_RECURSE SRC_FILES src/*.c)
add_library(maghreb STATIC ${SRC_FILES})

enable_testing()

add_executable(maghreb_test test/test.c)
target_link_libraries(maghreb_test maghreb)
add_test(NAME maghreb_test COMMAND maghreb_test)
