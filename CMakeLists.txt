cmake_minimum_required(VERSION 2.6)
project(InlinedHashTable)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -stdlib=libstdc++")
set(CMAKE_CXX_COMPILER "/opt/clang+llvm-4.0.0-x86_64-linux-gnu-ubuntu-16.04/bin/clang++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath=/opt/clang+llvm-4.0.0-x86_64-linux-gnu-ubuntu-16.04/lib")
include(ExternalProject)

ExternalProject_Add (
 project_benchmark
 PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
 GIT_REPOSITORY "https://github.com/google/benchmark.git"
 GIT_TAG "7a74b74856bae690a0998c967c7807dd2272af82"
 UPDATE_COMMAND ""
 INSTALL_COMMAND "")

ExternalProject_Get_Property(project_benchmark install_dir)

add_library(benchmark STATIC IMPORTED)
set_property(
  TARGET benchmark
  PROPERTY IMPORTED_LOCATION
  benchmark/src/project_benchmark-build/src/libbenchmark.a)
add_dependencies(benchmark project_benchmark)

include_directories(benchmark/src/project_benchmark/include)
link_directories(/home/saito/boyer_moore)
add_executable(boyer_moore_test boyer_moore_test.cc)

target_link_libraries(
  boyer_moore_test
  benchmark ${GTEST_LIBRARIES} pthread)
