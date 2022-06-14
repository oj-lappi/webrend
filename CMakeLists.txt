cmake_minimum_required( VERSION 3.10.1 )
include(${CMAKE_SOURCE_DIR}/cmake/DefaultCompilers.cmake)

project(WebRend)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ENABLE_ADDRESS_SANITIZER "Turn on -fsanitize=address" OFF)
option(ENABLE_PERFORMANCE_TRACES "Set -fno-omit-frame-pointer for readable labels" OFF)

option(BUILD_MICROBENCHMARKS "Build the microbenchmarks in \"benchmarks\"" OFF)
option(INTRUSIVE_PROFILING "Build with intrusive profiling in select functions" OFF)

include(${CMAKE_SOURCE_DIR}/cmake/BuildOptimization.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/StaticAnalysis.cmake)

enable_testing()

add_subdirectory(src)

if(BUILD_MICROBENCHMARKS)
    add_subdirectory(benchmarks)
endif()
