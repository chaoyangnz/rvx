cmake_minimum_required (VERSION 3.13)
set(CMAKE_C_COMPILER_WORKS "STATIC_LIBRARY")
project(arvos C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_VERBOSE_MAKEFILE ON)

##################### CROSS COMPILING TOOL CHAIN ############################

set(RISCV "/opt/riscv/bin/riscv64-unknown-elf")

# Toolchain
set(CMAKE_AR "${RISCV}-ar")
set(CMAKE_RANLIB  "${RISCV}-ranlib")
set(CMAKE_ASM_COMPILER "${RISCV}-gcc")
set(CMAKE_C_COMPILER "${RISCV}-gcc")
set(CMAKE_LINKER ${RISCV}-ld)
set(CMAKE_C_FLAGS "")
set(CMAKE_ASM_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")
include_directories(${CMAKE_SOURCE_DIR})

# kernel
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
#set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(C_FLAGS -Wall -Werror -O -fno-omit-frame-pointer -MD -mcmodel=medany -ffreestanding -fno-common -nostdlib -mno-relax -I. -fno-stack-protector -fno-pie -no-pie)
set(ASM_FLAGS "")
set(LD_FLAGS -z max-page-size=4096 ${C_FLAGS})

add_executable(kernel
    # entry.S must be the first one
    kernel/entry.S
    kernel/start.c
    kernel/console.c
    kernel/printf.c
    kernel/uart.c
    kernel/kalloc.c
    kernel/spinlock.c
    kernel/string.c
    kernel/main.c
    kernel/vm.c
    kernel/proc.c
    kernel/swtch.S
    kernel/trampoline.S
    kernel/trap.c
    kernel/syscall.c
    kernel/sysproc.c
    kernel/bio.c
    kernel/fs.c
    kernel/log.c
    kernel/sleeplock.c
    kernel/file.c
    kernel/pipe.c
    kernel/exec.c
    kernel/sysfile.c
    kernel/kernelvec.S
    kernel/plic.c
    kernel/ramdisk.c
    kernel/d1_clock.c
    kernel/d1_gpio.c
    kernel/d1_uart.c
)

target_compile_options(kernel PRIVATE
        $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
        $<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>
)
target_link_options(kernel PRIVATE ${LD_FLAGS} -T ${CMAKE_SOURCE_DIR}/kernel/kernel.ld)


add_custom_command (TARGET kernel
    POST_BUILD
    COMMAND cp -rf kernel ${CMAKE_PROJECT_NAME}.elf
    COMMAND ${RISCV}-objdump -d -D kernel > ${CMAKE_PROJECT_NAME}.objdump
    COMMAND ${RISCV}-objdump -S kernel > ${CMAKE_PROJECT_NAME}.asm
    COMMAND ${RISCV}-objcopy -S -O binary kernel ${CMAKE_PROJECT_NAME}.bin
    COMMAND hexdump ${CMAKE_PROJECT_NAME}.bin > arvos.hexdump
    COMMENT "Make kernel binary & dump"
)


############ user ############
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/user/usys.S
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND perl user/usys.pl > user/usys.S
)

add_library(ulib user/ulib.c user/printf.c user/umalloc.c user/usys.S)
target_compile_options(ulib PRIVATE ${CMAKE_C_FLAGS})

set(USER_PROGRAMS init cat echo grep kill ln ls mkdir rm sh wc pyramid)
set(USER_PROGRAM_PATHS)
foreach(USER_PROGRAM ${USER_PROGRAMS})
    add_executable(${USER_PROGRAM} user/${USER_PROGRAM}.c)

    target_compile_options(${USER_PROGRAM} PRIVATE ${C_FLAGS})
    target_link_options(${USER_PROGRAM} PRIVATE ${LD_FLAGS} -N -e main -Ttext 0)
    target_link_libraries(${USER_PROGRAM} ulib)

    list(APPEND USER_PROGRAM_PATHS ${CMAKE_CURRENT_BINARY_DIR}/${USER_PROGRAM})
endforeach()

############ mkfs ############
# build mkfs cli
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/mkfs/mkfs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND gcc -Werror -Wall -I. -o mkfs/mkfs mkfs/mkfs.c
)

add_custom_target(ramdisk ALL DEPENDS ${CMAKE_SOURCE_DIR}/mkfs/mkfs ${USER_PROGRAM_PATHS})

add_custom_command(TARGET ramdisk
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND mkfs/mkfs fs.img README.md ${USER_PROGRAM_PATHS}
    COMMAND xxd -i fs.img > kernel/ramdisk.h
)
