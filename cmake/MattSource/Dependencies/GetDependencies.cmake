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

include (MattSource/Dependencies/GetNexusSettings)
include (MattSource/Dependencies/GetDepsFile)
include (MattSource/Dependencies/GetDependency)

function(MSource_GetDependencies)
  message(STATUS "Using Nexus dependencies - reading settings...")
  MSource_GetNexusSettings(NEXUS_URL NEXUS_USERNAME NEXUS_PASSWORD NEXUS_VERSION NEXUS_OS NEXUS_ADDRESS_MODEL NEXUS_PLATFORM_COMPILER)
  message(STATUS "Developer: ${NEXUS_USERNAME}, Nexus URL: ${NEXUS_URL}, Nexus Version: ${NEXUS_VERSION}")
  message(STATUS "Nexus will look for deps using: ${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}")

  MSource_GetDepsFile(DEPS_FILE NUM_OF_DEPS)
  message(STATUS "Found ${NUM_OF_DEPS} dependencies. Fetching...")

  foreach(DEP ${DEPS_FILE})
    string(REPLACE " " ";" TMP_LIST ${DEP})
    list(GET TMP_LIST 0 TMP_DEP_GROUP)
    list(GET TMP_LIST 1 TMP_DEP_NAME)
    list(GET TMP_LIST 2 TMP_DEP_VER)
    list(LENGTH TMP_LIST TMP_LIST_LENGTH)
    if (${TMP_LIST_LENGTH} GREATER 3)
      list(GET TMP_LIST 3 TMP_DEP_NOARCH)
    else()
      set(TMP_DEP_NOARCH 0)
    endif()
    MSource_GetDependency(${TMP_DEP_GROUP} ${TMP_DEP_NAME} ${TMP_DEP_VER} ${TMP_DEP_NOARCH} ${NEXUS_URL} ${NEXUS_USERNAME} ${NEXUS_PASSWORD} ${NEXUS_VERSION} ${NEXUS_OS} ${NEXUS_ADDRESS_MODEL} ${NEXUS_PLATFORM_COMPILER})
    unset(TMP_DEP_VER)
    unset(TMP_DEP_NAME)
    unset(TMP_DEP_GROUP)
    unset(TMP_DEP_NOARCH)
    unset(TMP_LIST)
  endforeach()
endfunction()
