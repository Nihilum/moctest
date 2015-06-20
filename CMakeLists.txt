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

# Make sure that we can find all CMake includes
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/cmake/MattSource/Libraries)

include(MattSource/MattSource)

MSource_ForceOutOfSourceBuild()
MSource_DetermineAddressModel(MSOURCE_ADDRESS_MODEL)
message(STATUS "Detected ${MSOURCE_ADDRESS_MODEL}-bit address model.")

set(USE_DEPS "TRUE" CACHE BOOL "Use deps.txt file and artifactory")

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
