cmake_minimum_required(VERSION 3.20)

set(LIB_NAME FatFs_App)

file(GLOB sources
  ${CMAKE_CURRENT_LIST_DIR}/App/*.c
  ${CMAKE_CURRENT_LIST_DIR}/Target/*.c
)

file(GLOB headers
  ${CMAKE_CURRENT_LIST_DIR}/App/*.h
  ${CMAKE_CURRENT_LIST_DIR}/Target/*.h
)

set(includes
  ${CMAKE_CURRENT_LIST_DIR}/App
  ${CMAKE_CURRENT_LIST_DIR}/Target
)

add_library(${LIB_NAME} INTERFACE)
add_library(app::FatFs_App ALIAS ${LIB_NAME})

target_sources(${LIB_NAME} INTERFACE ${sources} ${headers})
target_include_directories(${LIB_NAME} INTERFACE ${includes})

target_compile_definitions(${LIB_NAME} INTERFACE
)
