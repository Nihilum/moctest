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

function(MSource_GetDependency MSOURCE_GROUP MSOURCE_DEP MSOURCE_VER NEXUS_URL NEXUS_USERNAME NEXUS_PASSWORD NEXUS_OS NEXUS_ADDRESS_MODEL NEXUS_PLATFORM_COMPILER)
  set(TMP_PATH_GENERIC "${MSOURCE_DEP}-${NEXUS_OS}-${NEXUS_ADDRESS_MODEL}-${NEXUS_PLATFORM_COMPILER}")

  if(NOT EXISTS deps)
  endif()

  unset(TMP_FILENAME_GENERIC)
endfunction()
