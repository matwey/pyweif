cmake_minimum_required(VERSION 3.15)
project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ffast-math -fno-finite-math-only")

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)
find_package(xtensor REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(WEIF REQUIRED IMPORTED_TARGET weif)

nanobind_add_module(pyweif
	STABLE_ABI LTO NB_STATIC
	src/af.cpp
	src/af.h
	src/sf.cpp
	src/sf.h
	src/df.cpp
	src/function_ref.h
	src/spectral_response.cpp
	src/pyweif.cpp
	src/weight_function.cpp)
target_link_libraries(pyweif PRIVATE PkgConfig::WEIF)
target_compile_definitions(pyweif PRIVATE VERSION_INFO="${PROJECT_VERSION}")
set_property(TARGET pyweif PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
set_property(TARGET pyweif PROPERTY CXX_VISIBILITY_PRESET hidden)

install(TARGETS pyweif DESTINATION .)
