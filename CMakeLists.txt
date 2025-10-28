# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake -DCMAKE_BUILD_TYPE=Debug .. or cmake -DCMAKE_BUILD_TYPE=Release ..
#   5. make
#   6. (Optional) cmake -DBUILD_DOC=ON .. && make doc

cmake_minimum_required(VERSION 3.20)  # For C++23 support

# Set compiler before project() declaration
set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")    # Use g++-13

# set the project name 
project(primitive-recursive-function               # Mandatory
    VERSION 1.0
    DESCRIPTION "primitive-recursive-function problem"
    LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23) 						# Use c++23
set(CMAKE_CXX_STANDARD_REQUIRED True)

# tell cmake to output binaries here:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# tell cmake where to look for *.h files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Automatically add all .cc files
file(GLOB_RECURSE ALL_CC_FILES "${PROJECT_SOURCE_DIR}/src/*.cc")

add_executable(primitive-recursive-function ${ALL_CC_FILES})

# Add expected compiler features to a target.
target_compile_features(primitive-recursive-function PRIVATE cxx_std_23)

# Add compile options to a target.
target_compile_options(primitive-recursive-function PRIVATE -Wall -Wextra -Wpedantic -Weffc++)

# Option to build documentation
option(BUILD_DOC "Build documentation" OFF)

# Check if Doxygen is installed and BUILD_DOC is ON
if(BUILD_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)

        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
        
        message(STATUS "Doxygen documentation target 'doc' added. Run 'make doc' to generate documentation.")
    else()
        message(WARNING "Doxygen not found. Documentation will not be generated.")
    endif()
endif()