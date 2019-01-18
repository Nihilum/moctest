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

function(MSource_GetNexusFile MSOURCE_NEXUS_URL MSOURCE_NEXUS_USERNAME MSOURCE_NEXUS_PASSWORD MSOURCE_NEXUS_VERSION)
  file(STRINGS nexus.txt NEXUS_FILE)
  list(GET NEXUS_FILE 0 TMP_NEXUS_URL)
  list(GET NEXUS_FILE 1 TMP_NEXUS_USERNAME)
  list(GET NEXUS_FILE 2 TMP_NEXUS_PASSWORD)
  list(GET NEXUS_FILE 3 TMP_NEXUS_VERSION)

  set(${MSOURCE_NEXUS_URL} ${TMP_NEXUS_URL} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_USERNAME} ${TMP_NEXUS_USERNAME} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_PASSWORD} ${TMP_NEXUS_PASSWORD} PARENT_SCOPE)
  set(${MSOURCE_NEXUS_VERSION} ${TMP_NEXUS_VERSION} PARENT_SCOPE)

  unset(TMP_NEXUS_URL)
  unset(TMP_NEXUS_USERNAME)
  unset(TMP_NEXUS_PASSWORD)
  unset(TMP_NEXUS_VERSION)
endfunction()
