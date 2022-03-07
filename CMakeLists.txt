cmake_minimum_required(VERSION 3.10)

project(lyhServer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

##set(CMAKE_CXX_FLAGS_DEBUG -g -std=c++11)

##set(CMAKE_CXX_FLAGS_RELEASE -g -std=c++11)
include_directories(${PROJECT_SOURCE_DIR})

message(status "project sdir: .....${PROJECT_SOURCE_DIR}")

add_subdirectory(common)
add_subdirectory(network)
add_subdirectory(test)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/test)

add_executable(testcore ./test/main.cpp)
