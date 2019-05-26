project (LMX)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -fopenmp -std=gnu++11 -gdwarf-3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")

add_subdirectory (tests)

enable_testing()

file(COPY tests DESTINATION ${PROJECT_BINARY_DIR})
