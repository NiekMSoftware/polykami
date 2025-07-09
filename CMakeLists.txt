cmake_minimum_required(VERSION 3.31)
project(Polykami VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# option to build examples
option(POLYKAMI_BUILD_EXAMPLES "Build examples" OFF)

# libraries
add_subdirectory(extern)

# engine
add_subdirectory(src)

# build examples if enabled
if (POLYKAMI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()