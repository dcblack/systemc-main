#!cmake .
# This works with SystemV versions 2.3.2 and later, which have support for
# cmake and specify SystemC_CXX_STANDARD.
# 
# REQUIREMENTS:
#   Define SYSTEMC_HOME to point to install directory of SystemC (not source)

cmake_minimum_required(VERSION 3.11)
set(TARGET_EXECUTABLE $<TARGET_FILE_NAME:basic.x>)
project(basic CXX)

include(/apps/cmake/SystemC.cmake)

add_compile_definitions(SC_INCLUDE_FX SC_INCLUDE_DYNAMIC_PROCESSES)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-g -Wall -Wextra -pedantic -Werror)
endif()

add_executable(basic.x
  basic_main.cpp
  basic_top.cpp
  wallclock.cpp
  report.cpp
)
#target_compile_features(basic.x PUBLIC cxx_std_11)
#target_include_directories(basic.x includes)
#target_link_libraries(basic.x ${CMAKE_SOURCE_DIR}/lib{:YOUR_STATIC_LIB:}.a)
