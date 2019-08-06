cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0048 NEW)


## CONFIG

project(wrmath VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Don't warn on unused functions, because this is a library and not all
# functions might be used.
add_compile_options(-Werror -Wno-unused-function -Wall -g -O0)

if(DEFINED ENV{CMAKE_GCOV})
add_compile_options(-fprofile-arcs -ftest-coverage)
# Need CMake 3.15+.
add_link_options(-fprofile-arcs -ftest-coverage)
add_custom_target(coverage COMMAND lcov -d . -t wrmath -o wrmath.info -c -i
			   COMMAND lcov -d . -t wrmath -o wrmath.info -c
			   COMMAND lcov -d . -t wrmath -o wrmath.info -r wrmath.info *gtest*
			   COMMAND genhtml -o coverage-report wrmath.info)
message(STATUS, "Code coverage enabled.")
endif()


include_directories(include)

file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/**.h)
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES src/*.cc)

message("${${PROJECT_NAME}_SOURCES}	 -> libwrmath")

## BUILD

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
add_executable(euler2quat tools/euler2quat.cc)
target_link_libraries(euler2quat ${PROJECT_NAME})
set_target_properties(${TESTNAME} PROPERTIES
		FOLDER bin
		RUNTIME_OUTPUT_DIRECTORY bin)

## INSTALL

install(DIRECTORY include/${PROJECT_NAME}
	DESTINATION include/
	FILES_MATCHING PATTERN "*.h")


## TEST

# From Modern CMake:
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
include_directories("${gtest_SOURCE_DIR}/include")
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

include(CTest)
set(TEST_EXECS)
macro(package_add_gtest TESTNAME)
	add_executable(${TESTNAME} ${ARGN})
	target_link_libraries(${TESTNAME} gtest_main ${PROJECT_NAME})
	target_compile_options(${TESTNAME} PUBLIC ${GTEST_CFLAGS})
	add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
	set_target_properties(${TESTNAME} PROPERTIES
		FOLDER tests
		RUNTIME_OUTPUT_DIRECTORY tests)
	list(APPEND TEST_EXECS ${TESTNAME})
endmacro()

# define the tests
package_add_gtest(vector_test 		test/vector_test.cc)
package_add_gtest(orientation_test 	test/orientation_test.cc)
package_add_gtest(quaternion_test 	test/quaternion_test.cc)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS ${TEST_EXECS})


## DEPLOY

include(CMakePack.txt)


## DOCUMENTATE
add_subdirectory ("docs")
