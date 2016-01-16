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
# Find the GSL includes
#
# This module defines
# GSL_INCLUDE_DIR, where to find gsl.h, etc.
# GSL_FOUND, If false, do not try to use GSL.


file(GLOB DEPS_DIR ${GSL_ROOT})

foreach(DEP ${DEPS_DIR})
  if(DEP MATCHES "gsl.*")
    set(GSL_PATH ${DEP})
  endif()
endforeach()

FIND_PATH(GSL_INCLUDE_DIR gsl.h
  ${GSL_PATH}/include
  /usr/local/include
  /usr/include
)

IF(GSL_INCLUDE_DIR)
  SET(GSL_FOUND "YES")
ENDIF(GSL_INCLUDE_DIR)

if(GSL_FIND_REQUIRED AND NOT GSL_FOUND)
  message(SEND_ERROR "Unable to find the requested gsl includes. Make sure they are downloaded.")
endif()
