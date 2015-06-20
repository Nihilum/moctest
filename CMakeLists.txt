# The MIT License (MIT)
#
# Copyright (c) 2014-2015 Mateusz Kolodziejski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.2.2)
project(moctest CXX)

set(MOCTEST_VERSION 0.3.0)
set(MOCTEST_TAG dev)
set(MOCTEST_EMAIL matt@mattsource.com)
set(LIBRARY_NAME moctest)

add_definitions(
  -DMOCTEST_LIBRARY_VERSION_MAJOR=0
  -DMOCTEST_LIBRARY_VERSION_MINOR=3
  -DMOCTEST_LIBRARY_VERSION_PATCH=0
)

# Make sure that we can find all CMake includes
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/cmake/MattSource/Libraries)

include(MattSource/MattSource)

MSource_ForceOutOfSourceBuild()
MSource_DetermineAddressModel(MSOURCE_ADDRESS_MODEL)
message(STATUS "Detected ${MSOURCE_ADDRESS_MODEL}-bit address model.")

set(USE_DEPS "TRUE" CACHE BOOL "Use deps.txt file and artifactory")

# Prepare 3rd party libraries

if (USE_DEPS)
  MSource_GetDependencies()
  MSource_AdjustBoost()
  MSource_Adjustcppunit()

  file(GLOB DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/*)
  set(BOOST_ROOT ${DEPS_DIR})
  set(CPPUNIT_ROOT ${DEPS_DIR})
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(cppunit REQUIRED)

# Prepare project

# Compile flags
if(WIN32 AND NOT MINGW)
  # Disable dll-external warnings for Visual Studio; [/GS-] disable buffer overflow security checks (optimization)
  set(LIBRARY_COMPILE_FLAGS ${LIBRARY_COMPILE_FLAGS} "-DMOCTEST_DLL=1 /wd4251 /wd4275 /wd4351 /GS-")
else()
  # Activate C++11 mode for GNU/GCC
  set(LIBRARY_COMPILE_FLAGS ${LIBRARY_COMPILE_FLAGS} "-std=c++11 -DMOCTEST_DLL=1")
endif()

# Source files and includes
file(GLOB_RECURSE LIBRARY_SRCS ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/include/*.hpp)

# Link directories
link_directories(${Boost_LIBRARY_DIR})

# Include dirs
include_directories(
  ${CMAKE_SOURCE_DIR}/include/
  ${CPPUNIT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
)

# Compilation definitions
add_definitions( ${Boost_LIB_DIAGNOSTIC_DEFINITIONS} ) # http://www.cmake.org/cmake/help/v3.2/module/FindBoost.html
add_definitions( -DBOOST_ALL_DYN_LINK ) # use boost dlls

if (MINGW)
  #add_definitions( -D_GLIBCXX_HAVE_STDINT_H ) # cstdint -> stdint.h
  add_definitions(-std=c++11)
endif()

# Properly setup RPATH (Linux)
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Specify that this project will build a library
add_library(${LIBRARY_NAME} SHARED
  ${LIBRARY_SRCS}
)

# Link libraries
target_link_libraries(${LIBRARY_NAME}
  debug ${CPPUNIT_DEBUG_LIBRARY}
  optimized ${CPPUNIT_LIBRARY}
  debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG}
  optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
)

# Use helper variable to link in tests
set(MOCTEST_LIB ${LIBRARY_NAME})


