cmake_minimum_required(VERSION 3.0.0)
project(NeuralNetwork VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(NeuralNetwork ${SOURCES})
target_include_directories(NeuralNetwork PRIVATE "include/")
target_include_directories(NeuralNetwork PRIVATE "/usr/include/eigen3")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
