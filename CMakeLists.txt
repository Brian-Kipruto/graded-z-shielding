#----------------------------------------------------------------------------
# Project setup
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(graded-z-shielding VERSION 0.1.0 LANGUAGES CXX)

# C++17 is what Geant4 11.x expects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------------------------------------------------------------
# Find Geant4
#----------------------------------------------------------------------------
# Use Geant4 with all UI and visualization drivers (Qt, OpenGL, etc.)
find_package(Geant4 REQUIRED ui_all vis_all)

# Pull in Geant4's compile flags, include paths, and library list
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Source files
#----------------------------------------------------------------------------
# Our header files live in include/
include_directories(${PROJECT_SOURCE_DIR}/include)

# Gather all .cc files in src/ automatically
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Build the executable
#----------------------------------------------------------------------------
add_executable(graded-z main.cc ${sources} ${headers})
target_link_libraries(graded-z ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy macro files to the build directory
#----------------------------------------------------------------------------
# This means after `make`, vis.mac etc. are next to the binary
file(GLOB MACRO_FILES "${PROJECT_SOURCE_DIR}/macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#----------------------------------------------------------------------------
# Install target (optional, ignore for now)
#----------------------------------------------------------------------------
install(TARGETS graded-z DESTINATION bin)