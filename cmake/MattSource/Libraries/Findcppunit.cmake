# The MIT License (MIT)
#
# Copyright (c) 2014-2016 Mateusz Kolodziejski
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
#
# This file is based on:
# http://www.cmake.org/pipermail/cmake/2006-October/011446.html
#
# Find the CppUnit includes and library
#
# This module defines
# CPPUNIT_INCLUDE_DIR, where to find tiff.h, etc.
# CPPUNIT_LIBRARIES, the libraries to link against to use CppUnit.
# CPPUNIT_FOUND, If false, do not try to use CppUnit.

# also defined, but not for general use are
# CPPUNIT_LIBRARY, where to find the CppUnit library.
# CPPUNIT_DEBUG_LIBRARY, where to find the CppUnit library in debug mode.


file(GLOB DEPS_DIR ${CPPUNIT_ROOT})

foreach(DEP ${DEPS_DIR})
  if(DEP MATCHES "cppunit.*debug")
    set(CPPUNIT_PATH_DEBUG ${DEP})
  endif()
  if(DEP MATCHES "cppunit.*release")
    set(CPPUNIT_PATH_RELEASE ${DEP})
  endif()
endforeach()

FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h
  ${CPPUNIT_PATH_RELEASE}/include
  /usr/local/include
  /usr/include
)

# With Win32, important to have both
IF(WIN32 AND NOT MINGW)
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_PATH_RELEASE}/lib
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunitd
               ${CPPUNIT_PATH_DEBUG}/lib
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
ELSE(WIN32 AND NOT MINGW)
  # On unix system, debug and release have the same name
  FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
               ${CPPUNIT_PATH_RELEASE}/lib
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_LIBRARY_INSTALL cppunit-1-13-0
               ${CPPUNIT_PATH_RELEASE}/bin
               ${CPPUNIT_INCLUDE_DIR}/../bin
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
               ${CPPUNIT_PATH_DEBUG}/lib
               ${CPPUNIT_INCLUDE_DIR}/../lib
               /usr/local/lib
               /usr/lib)
  FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY_INSTALL cppunit-1-13-0
               ${CPPUNIT_PATH_DEBUG}/bin
               ${CPPUNIT_INCLUDE_DIR}/../bin
               /usr/local/lib
               /usr/lib)
ENDIF(WIN32 AND NOT MINGW)

IF(CPPUNIT_INCLUDE_DIR)
  IF(CPPUNIT_LIBRARY)
    SET(CPPUNIT_FOUND "YES")
    SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY} ${CMAKE_DL_LIBS})
    SET(CPPUNIT_DEBUG_LIBRARIES ${CPPUNIT_DEBUG_LIBRARY}
${CMAKE_DL_LIBS})
  ENDIF(CPPUNIT_LIBRARY)
ENDIF(CPPUNIT_INCLUDE_DIR)

if(cppunit_FIND_REQUIRED AND NOT CPPUNIT_FOUND)
  message(SEND_ERROR "Unable to find the requested cppunit libraries. Make sure they are downloaded.")
endif()
