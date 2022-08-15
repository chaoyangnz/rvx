cmake_minimum_required (VERSION 3.13)
set(CMAKE_C_COMPILER_WORKS "STATIC_LIBRARY")
project(arvos)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_VERBOSE_MAKEFILE ON)

##################### CROSS COMPILING TOOL CHAIN ############################

set(RISCV "/opt/riscv/bin/riscv64-unknown-elf")

# BINUTILS
set(CMAKE_AR "${RISCV}-ar")
set(CMAKE_RANLIB  "${RISCV}-ranlib")

# ASM
enable_language(ASM)
set(CMAKE_ASM_FLAGS "" )
set(CMAKE_ASM_COMPILER "${RISCV}-gcc")
set(CMAKE_ASM_COMPILE_OBJECT "${CMAKE_ASM_COMPILER} -c -o <OBJECT> <SOURCE>")

# C COMPILER
enable_language(C)
set(CMAKE_C_COMPILER "${RISCV}-gcc")
set(CMAKE_C_FLAGS "-Wall -Werror -O -fno-omit-frame-pointer -MD -mcmodel=medany -ffreestanding -fno-common -nostdlib -mno-relax -I. -fno-stack-protector -fno-pie -no-pie")
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(CMAKE_C_FLAGS_RELEASE "")

# LINKER
set(CMAKE_LINKER ${RISCV}-ld)
set(CMAKE_EXE_LINKER_FLAGS "-z max-page-size=4096 -T ${CMAKE_SOURCE_DIR}/kernel/kernel.ld")

#file(GLOB_RECURSE LIBC_SRCS "libc/*.c" "libc/*.h")

file(GLOB_RECURSE KERNEL_SRCS "kernel/*.c" "kernel/*.S" "kernel/*.c")

# headers path
#include_directories(libc/include)

# libc for kernel only
#add_library(c STATIC ${LIBC_SRCS})
#target_link_libraries(c)

# kernel
add_executable(${CMAKE_PROJECT_NAME} ${KERNEL_SRCS})
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
#target_link_libraries(${CMAKE_PROJECT_NAME} c)

add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND ${RISCV}-objdump -d -D arvos.elf > arvos.objdump && ${RISCV}-objdump -S arvos.elf > arvos.asm && ${RISCV}-objcopy -S -O binary arvos.elf arvos.bin && hexdump arvos.bin > arvos.hexdump
        COMMENT "COPY kernel to another file")






