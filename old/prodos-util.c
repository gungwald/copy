#include <string.h> /* size_t */
#include "prodos.h"

struct ProdosPathName *
prodosAssignPathName(struct ProdosPathName *dest, const char *src)
{
    size_t i;
    char c;
    char *name;

    name = dest->name;
    for (i = 0; i < PRODOS_MAX_PATHNAME_LENGTH && (c = src[i]) != '\0'; ++i) {
        name[i] = c;
    }
    dest->length = i;
    return dest;
}

char *
prodosGetMessage(enum ProdosErrorCode code)
{
    char *message;

    switch (code) {
        case PRODOS_ERR_NO_ERROR:
            message = "No error";
            break;
        case PRODOS_ERR_BAD_SYS_CALL_NUM:
            message = "Bad system call number";
            break;
        case PRODOS_ERR_BAD_PARAM_COUNT:
            message = "Bad parameter count";
            break;
        case PRODOS_ERR_INTR_VECT_TBL_FULL:
            message = "Interrupt vector table full";
            break;
        default:
            message = "Unknown error";
    }
    return message;
}

