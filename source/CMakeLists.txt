cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory-dll
  VERSION 0.1.0
  LANGUAGES C
)

file(
    GLOB src_synapse_memory_dll CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)
add_subdirectory(lib)

add_library(
  synapse_memory_dll SHARED ${src_synapse_memory_dll}
)

target_include_directories(
  synapse_memory_dll PUBLIC ${CMAKE_SOURCE_DIR}/../include
)

target_compile_options(
  synapse_memory_dll PRIVATE /Dsynapse_memory_export_mode
)

target_link_libraries(
  synapse_memory_dll synapse_memory_lib
)