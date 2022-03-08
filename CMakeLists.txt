cmake_minimum_required(VERSION 3.10)

project(lyhServer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

#set(CMAKE_CXX_FLAGS_DEBUG -g -std=c++17)
#set(CMAKE_CXX_FLAGS_RELEASE -g -std=c++17)
set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR})

#message(status "project sdir: .....${PROJECT_SOURCE_DIR}")
#message(status "LIBRARY_OUTPUT_PATH: .....${LIBRARY_OUTPUT_PATH}")

add_subdirectory(common)
add_subdirectory(network)
add_subdirectory(test)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libs) 

#message(status "LIBRARY_OUTPUT_PATH: .....${LIBRARY_OUTPUT_PATH}")

