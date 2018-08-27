#!cmake .
# This works with SystemV versions 2.3.2 and later, which have support for
# cmake and specify SystemC_CXX_STANDARD.
# 
# REQUIREMENTS:
#   Define SYSTEMC_HOME to point to install directory of SystemC (not source)

cmake_minimum_required(VERSION 3.11)

project(basic CXX)

include(CMakeSystemC.txt)

add_compile_definitions(SC_INCLUDE_FX SC_INCLUDE_DYNAMIC_PROCESSES)

add_executable(basic.x
  basic_main.cpp
  basic_top.cpp
  wallclock.cpp
)
#target_compile_features(basic.x PUBLIC cxx_std_11)
#target_include_directories(basic.x includes)
#target_link_libraries(basic.x ${CMAKE_SOURCE_DIR}/lib{:YOUR_STATIC_LIB:}.a)
