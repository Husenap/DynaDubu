cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "dyna-dubu")
project(${PROJECT_NAME} C CXX)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "predefined")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")
include("cmake/conan.cmake")
include("cmake/util.cmake")

include(GoogleTest)
enable_testing()

add_subdirectory("dyna-dubu")
add_subdirectory("example")
