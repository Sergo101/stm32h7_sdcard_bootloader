cmake_minimum_required(VERSION 3.22)

#
# User is free to modify the file as much as necessary
#

list(APPEND CMAKE_MODULE_PATH "{{sr:cmake_path}}")
message("Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
include("cmake/gcc-arm-none-eabi.cmake")
message("Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# Core project settings
project(qspi_loader)
enable_language(C CXX ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_definitions(-DSTM32H750xx)

# Core MCU flags, CPU, instruction set and FPU setup
set(cpu_PARAMS ${cpu_PARAMS}
    -mthumb

    # Other parameters
    # -mcpu, -mfloat, -mfloat-abi, ...
    -mcpu=cortex-m7
	-mfpu=fpv5-d16
	-mfloat-abi=hard
	
)


# Setup all necessary include directories
# These are used by compiler to search for C or C++ headers

# Sources
set(sources_SRCS
${CMAKE_CURRENT_LIST_DIR}/Core/Src/bootloader.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/BspQspiBoot.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/gpio.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/main.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/quadspi.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/sdmmc.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32h7xx_hal_msp.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/stm32h7xx_it.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/syscalls.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/sysmem.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/system_stm32h7xx.c
${CMAKE_CURRENT_LIST_DIR}/Core/Src/usart.c
${CMAKE_CURRENT_LIST_DIR}/Core/Startup/startup_stm32h750ibkx.s
)

# Include directories for all compilers
set(include_DIRS
${CMAKE_CURRENT_LIST_DIR}/Core/Inc
)

# Include directories for each compiler
set(include_c_DIRS
${CMAKE_CURRENT_LIST_DIR}/Core/Inc
)
set(include_cxx_DIRS)
set(include_asm_DIRS)

# Symbols definition for all compilers
set(symbols_SYMB
# USE_HAL_DRIVER
# STM32H750xx
)

# Symbols definition for each compiler
set(symbols_c_SYMB)
set(symbols_cxx_SYMB)
set(symbols_asm_SYMB)

# Link directories and names of libraries
set(link_DIRS)
set(link_LIBS
hal_stm32h7xx
cmsis_stm32h7xx
FatFs
FatFs_App
)



# Compiler options
set(compiler_OPTS)

# Linker options
set(linker_OPTS)

add_subdirectory(Drivers/CMSIS)
add_subdirectory(Drivers/STM32H7xx_HAL_Driver)
add_subdirectory(Middlewares/Third_Party/FatFs)
add_subdirectory(FATFS)

# Link directories setup
# Must be before executable is added
link_directories(${CMAKE_PROJECT_NAME} ${link_DIRS})

# Linker script
set(linker_script_SRC ${linker_script_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32h750ibkx_FLASH.ld
)
# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${sources_SRCS})

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${include_DIRS}
    $<$<COMPILE_LANGUAGE:C>: ${include_c_DIRS}>
    $<$<COMPILE_LANGUAGE:CXX>: ${include_cxx_DIRS}>
    $<$<COMPILE_LANGUAGE:ASM>: ${include_asm_DIRS}>
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ${symbols_SYMB}
    $<$<COMPILE_LANGUAGE:C>: ${symbols_c_SYMB}>
    $<$<COMPILE_LANGUAGE:CXX>: ${symbols_cxx_SYMB}>
    $<$<COMPILE_LANGUAGE:ASM>: ${symbols_asm_SYMB}>

    # Configuration specific
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>: >
)



# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${link_LIBS})

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    ${cpu_PARAMS}
    ${compiler_OPTS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:C>: >
    $<$<COMPILE_LANGUAGE:CXX>:

    # -Wno-volatile
    # -Wold-style-cast
    # -Wuseless-cast
    # -Wsuggest-override
    >
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>
)

# Linker options
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${linker_script_SRC}
    ${cpu_PARAMS}
    ${linker_OPTS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -u _printf_float # STDIO float formatting support (remove if not used)
    --specs=nosys.specs
    # --specs=nano.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,-z,max-page-size=8 # Allow good software remapping across address space (with proper GCC section making)
    -Wl,--print-memory-usage
)

# Execute post-build to print size, generate hex and bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)
