# The MIT License (MIT)
#
# Copyright (c) 2014-2019 Mateusz Kolodziejski
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

include(MattSource/Dependencies/GetNexusFile)
include(MattSource/Dependencies/GetNexusOS)
include(MattSource/Dependencies/GetNexusAddressModel)
include(MattSource/Dependencies/GetNexusPlatformCompiler)

function(MSource_GetNexusSettings MSOURCE_NEXUS_URL MSOURCE_NEXUS_USERNAME MSOURCE_NEXUS_PASSWORD MSOURCE_NEXUS_VERSION MSOURCE_NEXUS_OS MSOURCE_NEXUS_ADDRESS_MODEL MSOURCE_NEXUS_PLATFORM_COMPILER)
  MSource_GetNexusFile(TMP_NEXUS_URL TMP_NEXUS_USERNAME TMP_NEXUS_PASSWORD TMP_NEXUS_VERSION)
  MSource_GetNexusOS(TMP_NEXUS_OS)
  MSource_GetNexusAddressModel(TMP_NEXUS_ADRESS_MODEL)
  MSource_GetNexusPlatformCompiler(TMP_NEXUS_COMPILER_PLATFORM TMP_NEXUS_OS)

  set(${MSOURCE_NEXUS_URL} ${TMP_NEXUS_URL} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_USERNAME} ${TMP_NEXUS_USERNAME} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_PASSWORD} ${TMP_NEXUS_PASSWORD} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_VERSION} ${TMP_NEXUS_VERSION} PARENT_SCOPE)

  set(${MSOURCE_NEXUS_OS} ${TMP_NEXUS_OS} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_ADDRESS_MODEL} ${TMP_NEXUS_ADRESS_MODEL} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_PLATFORM_COMPILER} ${TMP_NEXUS_COMPILER_PLATFORM} PARENT_SCOPE)

  unset(TMP_NEXUS_URL)
  unset(TMP_NEXUS_USERNAME)
  unset(TMP_NEXUS_PASSWORD)
  unset(TMP_NEXUS_VERSION)

  unset(TMP_NEXUS_OS)
  unset(TMP_NEXUS_ADRESS_MODEL)
  unset(TMP_NEXUS_COMPILER_PLATFORM)
endfunction()
