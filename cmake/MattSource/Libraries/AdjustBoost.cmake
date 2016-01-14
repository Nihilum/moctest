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

function(MSource_AdjustBoost)
  if(ADJUSTED_BOOST)
    return()
  endif()

  file(GLOB DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/*)

  foreach(DEP ${DEPS_DIR})
    if(DEP MATCHES "boost.*debug")
      set(BOOST_PATH_DEBUG ${DEP})
    endif()
    if(DEP MATCHES "boost.*release")
      set(BOOST_PATH_RELEASE ${DEP})
    endif()
  endforeach()

  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${BOOST_PATH_RELEASE}/lib ${BOOST_PATH_DEBUG}/lib)
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${BOOST_PATH_DEBUG}/lib ${BOOST_PATH_RELEASE}/lib)

  set(ADJUSTED_BOOST "TRUE" CACHE BOOL "Boost has been adjusted.")
endfunction()
