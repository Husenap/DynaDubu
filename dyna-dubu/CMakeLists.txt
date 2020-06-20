set(target_name "dyna-dubu")

set(src_files
	"src/dyna-dubu/SharedLibrary.h"
	"src/dyna-dubu/SharedLibrary.cpp")

# Project
add_library(${target_name} STATIC ${src_files})

source_group("src" FILES "src/main.cpp")

target_include_directories(${target_name} INTERFACE "src")

target_link_libraries(${target_name} ${CMAKE_DL_LIBS})

set_target_properties(${target_name} PROPERTIES FOLDER ${PROJECT_NAME})

# Test dynamic library
add_library("dubu" SHARED "test/dubu/dubu.cpp")
add_library("mina" SHARED "test/mina/mina.cpp")

# Tests
add_executable(${target_name}_test "test/test.cpp")

target_link_libraries(${target_name}_test ${target_name})
target_link_libraries(${target_name}_test CONAN_PKG::gtest)

set_target_properties(${target_name}_test PROPERTIES FOLDER ${PROJECT_NAME})

gtest_discover_tests(${target_name}_test)
