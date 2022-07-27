cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory-dll
  VERSION 0.1.0
  LANGUAGES C
)

file(
  GLOB_RECURSE 
  src_synapse_memory_lib
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib/*.c
)

file(
  GLOB_RECURSE 
  src_synapse_memory_dll 
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
  synapse_memory_dll 
  SHARED 
  ${src_synapse_memory_dll}
  ${src_synapse_memory_lib}
)

target_include_directories(
  synapse_memory_dll 
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  ${CMAKE_SOURCE_DIR}/include
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties(
      synapse_memory_dll
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib/build
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    target_compile_options(
      synapse_memory_dll 
      PRIVATE
      /Dsynapse_memory_export_mode
    )
    target_compile_options(
      synapse_memory_dll 
      PRIVATE
      /DSYNAPSE_BUILD_ENVIRONMENT_MSVC
    )
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set_target_properties(
    synapse_memory_dll
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
    target_compile_options(
      synapse_memory_dll 
      PRIVATE 
      -Dsynapse_memory_export_mode
    )
endif()