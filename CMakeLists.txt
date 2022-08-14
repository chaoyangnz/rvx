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
set(CMAKE_ASM_FLAGS "-march=rv64imafdcv -mabi=lp64 -x assembler-with-cpp" )
set(CMAKE_ASM_COMPILER "${RISCV}-gcc")

# C COMPILER
enable_language(C)
set(CMAKE_C_COMPILER "${RISCV}-gcc")
set(CMAKE_C_SYSROOT_FLAG "")
set(CMAKE_C_FLAGS "-march=rv64imafdcv -mabi=lp64 -MD -mcmodel=medany -ffreestanding -fno-common -nostdlib -mno-relax -fno-stack-protector -O -Wall -Wextra -I. -fno-pie -no-pie")
set(CMAKE_C_FLAGS_DEBUG "-ggdb -gdwarf-2")
set(CMAKE_C_FLAGS_RELEASE "-O0")
set(CMAKE_CXX_COMPILER "${RISCV}-g++")
#add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# LINKER
set(CMAKE_LINKER ${RISCV}-ld)
set(CMAKE_C_LINK_FLAGS "-z max-page-size=4096")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T${CMAKE_SOURCE_DIR}/kernel/kernel.ld")

#file(GLOB_RECURSE LIBC_SRCS "libc/*.c" "libc/*.h")
file(GLOB_RECURSE KERNEL_SRCS "kernel/*.c" "kernel/*.S" "kernel/*.c")

# headers path
#include_directories(libc/include)

# libc for kernel only
#add_library(c STATIC ${LIBC_SRCS})
#target_link_libraries(c)

# kernel
add_executable(${CMAKE_PROJECT_NAME} ${KERNEL_SRCS})
#target_link_libraries(${CMAKE_PROJECT_NAME} c)

add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND ${RISCV}-objdump -d -D arvos > arvos.objdump && hexdump arvos > arvos.hexdump
        COMMENT "COPY kernel to another file")


# run kernel in QEMU
#if(CMAKE_BUILD_TYPE MATCHES Debug)
#    set(QEMU_FLAGS "-gdb tcp::1234 -S")
#endif()
#add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
#        POST_BUILD
#        COMMAND qemu-system-riscv32
#            -machine virt
#            -m 2G
#            -no-reboot
#            -no-shutdown ${QEMU_FLAGS}
#            -bios none
#            -kernel ${CMAKE_BINARY_DIR}/arvos
#            -nographic
#            -monitor telnet:127.0.0.1:4321,server,nowait
#            #-serial mon:stdio
#
#        COMMENT "Running arvos kernel...")



