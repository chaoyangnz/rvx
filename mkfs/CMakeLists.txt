############ mkfs ############
# build mkfs cli
add_custom_command(
    OUTPUT mkfs/mkfs
    COMMAND gcc -Werror -Wall -I. -o mkfs/mkfs mkfs/mkfs.c
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Build mkfs tool"
)

add_custom_command(
    OUTPUT  kernel/ramdisk.h
    COMMAND mkfs/mkfs fs.img README.md ${USER_PROGRAM_PATHS}
    COMMAND xxd -i fs.img > kernel/ramdisk.h
    DEPENDS mkfs/mkfs ${USER_PROGRAM_PATHS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Build ramdisk image"
)