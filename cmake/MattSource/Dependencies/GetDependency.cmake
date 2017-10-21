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

function(MSource_GetDependency MSOURCE_GROUP MSOURCE_DEP MSOURCE_VER MSOURCE_NOARCH NEXUS_URL NEXUS_USERNAME NEXUS_PASSWORD NEXUS_VERSION NEXUS_OS NEXUS_ADDRESS_MODEL NEXUS_PLATFORM_COMPILER)
  set(TMP_PATH_GENERIC "${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}-${MSOURCE_VER}")
  set(TMP_FILE_RELEASE "${TMP_PATH_GENERIC}-release")
  set(TMP_FILE_DEBUG "${TMP_PATH_GENERIC}-debug")

  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps)
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)
  endif()

  string(COMPARE EQUAL "${NEXUS_VERSION}" nexus3 IS_NEXUS3)
  string(COMPARE EQUAL "${NEXUS_VERSION}" nexus2 IS_NEXUS2)

  STRING(REGEX REPLACE "\\." "/" NEXUS3_GROUP ${MSOURCE_GROUP})

  if(MSOURCE_NOARCH)
    set(TMP_PATH_GENERIC "${MSOURCE_DEP}-${MSOURCE_NOARCH}-${MSOURCE_VER}")
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC})
      message(STATUS "Downloading ${TMP_PATH_GENERIC}.zip from nexus...")
      if(IS_NEXUS2)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/nexus/service/local/artifact/maven/redirect?r=public&g=${MSOURCE_GROUP}&a=${MSOURCE_DEP}-${MSOURCE_NOARCH}&v=${MSOURCE_VER}&p=zip" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC}.zip)
      elseif(IS_NEXUS3)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/repository/maven-public/${NEXUS3_GROUP}/${MSOURCE_DEP}-noarch/${MSOURCE_VER}/${MSOURCE_DEP}-noarch-${MSOURCE_VER}.zip" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC}.zip)
      else()
        message(FATAL_ERROR "Unsupported nexus version: ${NEXUS_VERSION}")
      endif()

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC}.zip)
        message(FATAL_ERROR "Could not download ${TMP_PATH_GENERIC}.zip...")
      endif()

      message(STATUS "Unpacking ${TMP_PATH_GENERIC}.zip...")
      execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC}.zip WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC})
        message(FATAL_ERROR "Could not unpack ${TMP_PATH_GENERIC}.zip... See if it exists in nexus.")
      endif()

      execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/deps/${TMP_PATH_GENERIC}.zip)
    else()
      message(STATUS "${TMP_PATH_GENERIC} is in cache.")
    endif()
  else()
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE})
      message(STATUS "Downloading ${TMP_FILE_RELEASE}.zip from nexus...")

      if(IS_NEXUS2)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/nexus/service/local/artifact/maven/redirect?r=public&g=${MSOURCE_GROUP}&a=${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}&v=${MSOURCE_VER}&p=zip&c=release" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE}.zip)
      elseif(IS_NEXUS3)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/repository/maven-public/${NEXUS3_GROUP}/${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}/${MSOURCE_VER}/${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}-${MSOURCE_VER}-release.zip" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE}.zip)
      else()
        message(FATAL_ERROR "Unsupported nexus version: ${NEXUS_VERSION}")
      endif()

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE}.zip)
        message(FATAL_ERROR "Could not download ${TMP_FILE_RELEASE}.zip...")
      endif()

      message(STATUS "Unpacking ${TMP_FILE_RELEASE}.zip...")
      execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE}.zip WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE})
        message(FATAL_ERROR "Could not unpack ${TMP_FILE_RELEASE}.zip... See if it exists in nexus.")
      endif()

      execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_RELEASE}.zip)
    else()
      message(STATUS "${TMP_FILE_RELEASE} is in cache.")
    endif()

    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG} )
      message(STATUS "Downloading ${TMP_FILE_DEBUG}.zip from nexus...")

      if(IS_NEXUS2)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/nexus/service/local/artifact/maven/redirect?r=public&g=${MSOURCE_GROUP}&a=${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}&v=${MSOURCE_VER}&p=zip&c=debug" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG}.zip)
      elseif(IS_NEXUS3)
        execute_process(COMMAND curl -L -u ${NEXUS_USERNAME}:${NEXUS_PASSWORD} "${NEXUS_URL}/repository/maven-public/${NEXUS3_GROUP}/${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}/${MSOURCE_VER}/${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}-${MSOURCE_VER}-debug.zip" -o ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG}.zip)
      else()
        message(FATAL_ERROR "Unsupported nexus version: ${NEXUS_VERSION}")
      endif()

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG}.zip)
        message(FATAL_ERROR "Could not download ${TMP_FILE_DEBUG}.zip...")
      endif()

      message(STATUS "Unpacking ${TMP_FILE_DEBUG}.zip...")
      execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG}.zip WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)

      if(NOT EXISTS ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG})
        message(FATAL_ERROR "Could not unpack ${TMP_FILE_DEBUG}.zip... See if it exists in nexus.")
      endif()

      execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/deps/${TMP_FILE_DEBUG}.zip)
    else()
      message(STATUS "${TMP_FILE_DEBUG} is in cache.")
    endif()
  endif()

  unset(TMP_FILENAME_GENERIC)
  unset(TMP_FILE_RELEASE)
  unset(TMP_FILE_DEBUG)
endfunction()
