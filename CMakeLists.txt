cmake_minimum_required(VERSION 3.0)

project(
  synapse-memory
  VERSION 0.1.0
  LANGUAGES C
)

add_subdirectory(source/lib)
add_subdirectory(source/lib_cpp)
add_subdirectory(source/shared_lib)

add_dependencies(
    synapse_memory_dll,
    synapse_memory_lib
)