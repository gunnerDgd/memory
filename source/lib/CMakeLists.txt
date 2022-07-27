cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory-lib
  VERSION 0.1.0
  LANGUAGES C
)

file(
  GLOB_RECURSE
  src_synapse_memory_lib
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
  synapse_memory_lib
  STATIC
  ${src_synapse_memory_lib}
)

target_include_directories(
  synapse_memory_lib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  ${CMAKE_SOURCE_DIR}/include
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_options(
    synapse_memory_lib
    /DSYNAPSE_BUILD_ENVIRONMENT_MSVC
  )
endif()