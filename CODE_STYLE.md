# C Code Style

## headers

For headers per component, it should only include `struct` definitions and `#define` constants. Some exceptions also include static function implementations if any.

defs.h includes all function and struct declarations distributed in other .h files.


## C source file

It should only include function implementations declared in defs.h and other static struct, static variables, static functions,

## declaration and implementation relationship

- public structs: 

| declare  | implement |
| -------- | --------- |
| defs.h   | \*.h      |

- public functions:

| declare  | implement |
| -------- | --------- |
| defs.h   | \*.c      |

- public #define constants:

| declare  | implement |
| -------- | --------- |
| \*.h     | \*.h      |

- internal constants, variables (static), functions (static)

| declare  | implement |
| -------- | --------- |
| \*.c     | \*.c      |
