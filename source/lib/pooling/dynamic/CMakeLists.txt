cmake_minimum_required(VERSION 3.0)

project(
    synapse-memory-pooling-dynamic
    VERSION 0.1.0
    LANGUAGES C
)

file(
    GLOB_RECURSE 
    src_synapse_memory_pooling_dynamic
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(
    synapse_memory_pooling_dynamic_lib
    STATIC
    ${src_synapse_memory_pooling_dynamic}
)

target_include_directories(
    synapse_memory_pooling_dynamic_lib 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(
    synapse_memory_pooling_dynamic_lib
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
)

target_include_directories(
    synapse_memory_pooling_dynamic_lib
    PRIVATE
    ${CMAKE_SOURCE_DIR}/submodules/synapse-structure/include
)