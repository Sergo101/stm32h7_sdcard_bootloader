cmake_minimum_required(VERSION 3.20)

set(LIB_NAME cmsis_stm32h7xx)

file(GLOB sources
  ${CMAKE_CURRENT_LIST_DIR}/Device/ST/STM32H7xx/Source/*.c
  ${CMAKE_CURRENT_LIST_DIR}/Device/ST/STM32H7xx/Source/*.cpp
)

file(GLOB headers
  ${CMAKE_CURRENT_LIST_DIR}/Include/*.*
  ${CMAKE_CURRENT_LIST_DIR}/Device/ST/STM32H7xx/Include/*.*
)

set(includes
  ${CMAKE_CURRENT_LIST_DIR}/Include
  ${CMAKE_CURRENT_LIST_DIR}/Device/ST/STM32H7xx/Include
)

add_library(${LIB_NAME} INTERFACE)
add_library(cmsis::stm32h7xx ALIAS ${LIB_NAME})

target_sources(${LIB_NAME} INTERFACE ${sources} ${headers})
target_include_directories(${LIB_NAME} INTERFACE ${includes})

target_compile_definitions(${LIB_NAME} INTERFACE
)
