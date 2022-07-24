cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory-lib
  VERSION 0.1.0
  LANGUAGES C
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/system)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mman/standard_heap)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mman/nonpaged)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pooling/static)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pooling/dynamic)

add_library(
  synapse_memory_lib
  INTERFACE
)

add_dependencies(
  synapse_memory_lib
  synapse_memory_pooling_dynamic_lib
  synapse_memory_pooling_static_lib
  synapse_memory_mman_standard_heap_lib
  synapse_memory_mman_nonpaged_lib
  synapse_memory_system_lib
)

target_link_libraries(
  synapse_memory_lib
  INTERFACE
  synapse_memory_pooling_dynamic_lib
  synapse_memory_pooling_static_lib
  synapse_memory_mman_standard_heap_lib
  synapse_memory_mman_nonpaged_lib
  synapse_memory_system_lib
)