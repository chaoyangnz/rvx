# kernel
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
#set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(C_FLAGS -Wall -Werror -O -fno-omit-frame-pointer -MD -mcmodel=medany -ffreestanding -fno-common -nostdlib -mno-relax -I. -fno-stack-protector -fno-pie -no-pie -march=rv64gc -mabi=lp64d)
set(ASM_FLAGS ${C_FLAGS})
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
    kernel/ramdisk.h
)
set_target_properties(kernel PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}.elf")

target_compile_options(kernel PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
    $<$<COMPILE_LANGUAGE:ASM>:${ASM_FLAGS}>
)
target_link_options(kernel PRIVATE ${LD_FLAGS} -T ${CMAKE_SOURCE_DIR}/kernel/kernel.ld)


add_custom_command (TARGET kernel
    POST_BUILD
    COMMAND ${RISCV}-objdump -d -D ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.elf.objdump
    COMMAND ${RISCV}-objdump -S ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.elf.asm
    COMMAND ${RISCV}-objcopy -S -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMAND hexdump ${CMAKE_PROJECT_NAME}.bin > rvx.hexdump
    COMMENT "Make kernel binary & dump"
)