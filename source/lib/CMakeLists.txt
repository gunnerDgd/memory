cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory-lib
  VERSION 0.1.0
  LANGUAGES C
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mman/standard_heap)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pooling/static)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pooling/dynamic)