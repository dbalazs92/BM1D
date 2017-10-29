# $Id: CMakeLists.txt 12345 2017-10-26 10:11:23 Demeter Balázs $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(BM1D)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Setup ROOT include directories and compile definitions
#
include(${ROOT_USE_FILE})

# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable
#
add_executable(BM1D BM1D.cc ${sources} ${headers})
target_link_libraries(BM1D ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS BM1D DESTINATION bin)
