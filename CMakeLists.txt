cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0048 NEW)


## CONFIG

project(wrnav VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Werror -Wall -g -O0)

if(DEFINED ENV{CMAKE_GCOV})
add_compile_options(-fprofile-arcs -ftest-coverage)
# Need CMake 3.15+.
add_link_options(-fprofile-arcs -ftest-coverage)
endif()

find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)

include_directories(include)


## BUILD

# add_library(LIBNAME
#     SOURCES
# )
# 
# add_executable(EXE_NAME MAIN)
# target_link_libraries(EXE_NAME LIBNAMES)
# add_dependencies(EXE_NAME LIBNAMES)


## INSTALL

install(DIRECTORY include/${PROJECT_NAME}
	DESTINATION include/
	FILES_MATCHING PATTERN "*.h")


## TEST

# From Modern CMake:
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
include(CTest)
set(TEST_EXECS)
macro(package_add_gtest TESTNAME)
	add_executable(${TESTNAME} ${ARGN})
	target_link_libraries(${TESTNAME} ${GTEST_LDFLAGS})
	target_compile_options(${TESTNAME} PUBLIC ${GTEST_CFLAGS})
	add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
	set_target_properties(${TESTNAME} PROPERTIES
		FOLDER tests
		RUNTIME_OUTPUT_DIRECTORY tests)
	list(APPEND TEST_EXECS ${TESTNAME})
endmacro()

package_add_gtest(vector_test test/vector_test.cc)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS ${TEST_EXECS})


## DEPLOY

include(CMakePack.txt)
