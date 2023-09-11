cmake_minimum_required(VERSION 3.10)
project(oop_lab_01)

add_compile_options(-pedantic -Wall)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_EXE lab1/test.cpp)
set(SOURCE_EXE lab1/main.cpp)
set(SOURCE_LIB lab1/box_cap.cpp)

find_package(GTest REQUIRED)
add_library(box_cap STATIC ${SOURCE_LIB})
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(main ${SOURCE_EXE})
add_executable(test ${TEST_EXE})

target_link_libraries(main box_cap ${GTEST_LIBRARIES})
target_link_libraries(test box_cap ${GTEST_LIBRARIES})
