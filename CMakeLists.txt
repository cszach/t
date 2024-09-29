cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0135 NEW)

project (t LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library

set(LIBRARY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(LIBRARY_SOURCES 
	${LIBRARY_SOURCE_DIR}/null.cpp
)

add_library(t STATIC ${LIBRARY_SOURCES})
target_include_directories(
	t
	PUBLIC
	${CMAKE_SOURCE_DIR}/include/
)

install(
	TARGETS t
	RUNTIME
	LIBRARY
)

# Executable

add_executable(cube src/cube.cpp)
target_link_libraries(cube PUBLIC t)

add_executable(cornell_box src/cornell_box.cpp)
target_link_libraries(cornell_box PUBLIC t)

add_executable(teapot src/teapot.cpp)
target_link_libraries(teapot PUBLIC t)

add_executable(triangle src/triangle.cpp)
target_link_libraries(triangle PUBLIC t)

# GoogleTest

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	t_test
	tests/main.cpp
)

target_link_libraries(
	t_test
	t
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(t_test)