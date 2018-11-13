#include <stdio.h>
#include <stdbool.h>
#include <string.h>     /* strlen */

#include "cui.h"
#include "prodos.h"
#include "prodosext.h"

#define ESC '\x1b'

static char *readLine(char *line, size_t capacity);
static void chomp(char *line);
static bool complete;
static uint8_t result;

bool inputFileName(const char *prompt, char *name, 
    size_t capacity, 
    struct GetFileInfoParams *params)
{
    complete = false;

    while (! complete) {
        printf(prompt);
        readLine(name, capacity);
        if (strlen(name) == 0) {
            puts("Aborting");
            break;
        }
        else if (name[0] == ESC) {
            puts("Escaping");
            break;
        }
        params->param_count = GET_FILE_INFO_PARAM_COUNT;
        params->pathname = name;
        printf("params address = %x\n", &(params->param_count));
        printf("params address = %x\n", params);
        result = get_file_info(params);
        if (result == PRODOS_E_NONE)
            complete = true;
        else
            fprintf(stderr, "%s: %s (code %d)\n", name, getMessage(result), result);
    }
    return complete;
}

char *readLine(char *line, size_t capacity)
{
    char *result;

    if ((result = fgets(line, capacity, stdin)) != NULL)
        chomp(line);
    else if (ferror(stdin))
        perror("stdin");

    return result;
}

void chomp(char *line)
{
    size_t i;
    char c;

    for (i = strlen(line); i > 0; ) {
        c = line[--i];
        if (c == '\r' || c == '\n')
            line[i] = '\0';
        else
            break;
    }
}

