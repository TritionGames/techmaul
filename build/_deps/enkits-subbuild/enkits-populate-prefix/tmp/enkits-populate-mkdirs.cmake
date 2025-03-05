# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-src"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-build"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/tmp"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/src/enkits-populate-stamp"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/src"
  "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/src/enkits-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/src/enkits-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/triph/source/repos/cellgame/build/_deps/enkits-subbuild/enkits-populate-prefix/src/enkits-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
