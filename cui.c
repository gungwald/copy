#include <stdio.h>
#include <stdbool.h>
#include <string.h>     /* strlen */

#include "cui.h"
#include "fileinfo.h"

static char *readLine(char *line, size_t capacity);
static void chomp(char *line);
static bool complete;

void inputFileName(const char *prompt, char *name, size_t capacity, struct FileInfo *f)
{
    complete = false;

    while (! complete) {
        printf(prompt);
        readLine(name, capacity);
        initFileInfo(f, name);
        if (exists(f)) {
            complete = true;
        }
        else {
            fprintf(stderr, "File '%s' does not exist\n", name);
        }
    }
}

char *readLine(char *line, size_t capacity)
{
    char *result;

    if ((result = fgets(line, capacity, stdin)) != NULL)
        chomp(line);
    else
        if (ferror(stdin))
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

