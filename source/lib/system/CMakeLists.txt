cmake_minimum_required(VERSION 3.0)

project(
    synapse-memory-system
    VERSION 0.1.0
    LANGUAGES C
)

file(
    GLOB_RECURSE
    src_synapse_memory_system
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_memory_system_lib
    STATIC
    ${src_synapse_memory_system}
)

target_include_directories(
    synapse_memory_system_lib 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(
    synapse_memory_system_lib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
)