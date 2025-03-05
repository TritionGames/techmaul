# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.25.1-msvc1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(imgui-populate NONE)



include(ExternalProject)
ExternalProject_Add(imgui-populate
                     "URL" "https://github.com/ocornut/imgui/archive/refs/tags/v1.91.3.zip"
                    SOURCE_DIR          "C:/Users/triph/Downloads/box2d-main/box2d-main/build/imgui"
                    BINARY_DIR          "C:/Users/triph/source/repos/cellgame/build/samples/imgui-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


