# The MIT License (MIT)
#
# Copyright (c) 2014-2017 Mateusz Kolodziejski
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

set(TEST_NAME moctest_list_tests)

set(TEST_SRCS
  TestListTests.hpp
  TestListTests.cpp
)

if(WIN32 AND NOT MINGW)
  # Disable dll-external warnings for Visual Studio; [/GS-] disable buffer overflow security checks (optimization)
  set(PROGRAM_COMPILE_FLAGS ${PROGRAM_COMPILE_FLAGS} "/wd4251 /wd4275 /GS-")
else()
  # Activate C++11 mode for GNU/GCC; set rpath to $ORIGIN so the shared library can be easily found
  set(PROGRAM_COMPILE_FLAGS ${PROGRAM_COMPILE_FLAGS} "-std=c++14")
endif()

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "\$ORIGIN")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(NOT DEFINED WIN32 AND NOT DEFINED MINGW)
  SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--enable-new-dtags")
endif()

link_directories(${Boost_LIBRARY_DIR})

add_executable(${TEST_NAME} ${TEST_SRCS})

target_link_libraries(${TEST_NAME}
  ${MOCTEST_LIB}
  debug ${CPPUNIT_DEBUG_LIBRARY}
  optimized ${CPPUNIT_LIBRARY}
)

set_target_properties(${TEST_NAME} PROPERTIES COMPILE_FLAGS
  "${PROGRAM_COMPILE_FLAGS}"
)

install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)
