#include <stdio.h>
#include <string.h>     /* strlen */

#include "io.h"
#include "prodos.h"
#include "prodosext.h"

#define ESC '\x1b'

static char *readLine(char *line, size_t capacity);
static void chomp(char *line);
static bool complete;
static uint8_t result;

bool inputFileName(const char *prompt, FilePath name) 
{
    complete = false;

    while (! complete) {
        printf(prompt);
        readLine(name, sizeof(name));
        if (strlen(name) == 0) {
            puts("Aborting");
            break;
        }
        else if (name[0] == ESC) {
            puts("Escaping");
            break;
        }
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

