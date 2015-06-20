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

function(MSource_Adjustcppunit)
  if(ADJUSTED_CPPUNIT)
    return()
  endif()

  file(GLOB DEPS_DIR ${CMAKE_SOURCE_DIR}/deps/*)

  foreach(DEP ${DEPS_DIR})
    if(DEP MATCHES "cppunit.*debug")
      set(CPPUNIT_PATH_DEBUG ${DEP})
    endif()
    if(DEP MATCHES "cppunit.*release")
      set(CPPUNIT_PATH_RELEASE ${DEP})
    endif()
  endforeach()

  file(GLOB CPPUNIT_REL_BIN ${CPPUNIT_PATH_RELEASE}/bin/*)

  foreach(CPPUNIT_REL_BIN_FILE ${CPPUNIT_REL_BIN})
    if(CPPUNIT_REL_BIN_FILE MATCHES "libcppunit*")
      set(CPPUNIT_FILEPATH_RELEASE ${CPPUNIT_REL_BIN_FILE})
    endif()
  endforeach()

  file(GLOB CPPUNIT_DEB_BIN ${CPPUNIT_PATH_DEBUG}/bin/*)

  foreach(CPPUNIT_DEB_BIN_FILE ${CPPUNIT_DEB_BIN})
    if(CPPUNIT_DEB_BIN_FILE MATCHES "libcppunit*")
      set(CPPUNIT_FILEPATH_DEBUG ${CPPUNIT_DEB_BIN_FILE})
    endif()
  endforeach()

  get_filename_component(CPPUNIT_FILE_RELEASE ${CPPUNIT_FILEPATH_RELEASE} NAME)
  get_filename_component(CPPUNIT_FILE_DEBUG ${CPPUNIT_FILEPATH_DEBUG} NAME)
  get_filename_component(CPPUNIT_FILE_RELEASE_EXT ${CPPUNIT_FILEPATH_RELEASE} EXT)
  get_filename_component(CPPUNIT_FILE_DEBUG_EXT ${CPPUNIT_FILEPATH_DEBUG} EXT)

  execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CPPUNIT_PATH_RELEASE}/bin/${CPPUNIT_FILE_RELEASE} ${CPPUNIT_PATH_RELEASE}/bin/libcppunit${CPPUNIT_FILE_RELEASE_EXT})
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CPPUNIT_PATH_DEBUG}/bin/${CPPUNIT_FILE_DEBUG} ${CPPUNIT_PATH_DEBUG}/bin/libcppunit${CPPUNIT_FILE_DEBUG_EXT})

  set(ADJUSTED_CPPUNIT "TRUE" CACHE BOOL "CPPUnit has been adjusted.")
endfunction()
