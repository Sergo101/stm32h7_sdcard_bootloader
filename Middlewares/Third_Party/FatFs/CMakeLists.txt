cmake_minimum_required(VERSION 3.20)

set(LIB_NAME FatFs)

file(GLOB sources
  ${CMAKE_CURRENT_LIST_DIR}/src/option/syscall.c
  ${CMAKE_CURRENT_LIST_DIR}/src/*.c
)

file(GLOB headers
  ${CMAKE_CURRENT_LIST_DIR}/src/*.h
)

set(includes
  ${CMAKE_CURRENT_LIST_DIR}/src
)

add_library(${LIB_NAME} INTERFACE)
add_library(lib::FatFs ALIAS ${LIB_NAME})

target_sources(${LIB_NAME} INTERFACE ${sources} ${headers})
target_include_directories(${LIB_NAME} INTERFACE ${includes})

target_compile_definitions(${LIB_NAME} INTERFACE
)
