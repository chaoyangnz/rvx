############ user ############
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/user/usys.S
    COMMAND perl user/usys.pl > user/usys.S
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generate usys.S"
)

add_library(ulib user/ulib.c user/printf.c user/umalloc.c user/usys.S)
target_compile_options(ulib PRIVATE ${C_FLAGS})

set(USER_PROGRAMS
    init
    cat
    echo
    grep
    kill
    ln
    ls
    mkdir
    rm
    sh
    wc
    pyramid
    forktest
    grind
    stressfs
    usertests
    zombie
)
set(USER_PROGRAM_PATHS)
foreach(USER_PROGRAM ${USER_PROGRAMS})
    add_executable(${USER_PROGRAM} user/${USER_PROGRAM}.c)

    target_compile_options(${USER_PROGRAM} PRIVATE ${C_FLAGS})
    target_link_options(${USER_PROGRAM} PRIVATE ${LD_FLAGS} -N -e main -Ttext 0)
    target_link_libraries(${USER_PROGRAM} ulib)

    list(APPEND USER_PROGRAM_PATHS ${CMAKE_CURRENT_BINARY_DIR}/${USER_PROGRAM})
endforeach()