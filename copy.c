#include <stdio.h>      /* fopen, fread, fwrite, fclose */
#include <stdbool.h>
#include <stdlib.h>     /* atexit */
#include <string.h>
#include "libgen.h"	/* basename */

#include "prodos.h"
#include "prodosext.h"
#include "cui.h"

#define BF_SIZ 2048

void cleanup(void);
FILE *openFile(const char *name, const char *mode);
void closeFile(FILE *f, const char *name);
void concatPath(char *dest, const char *src);

char srcName[PRODOS_PATH_MAX + 1];
char destName[PRODOS_PATH_MAX + 1];
FILE *src = NULL;
FILE *dest = NULL;
struct GetFileInfoParams srcInfo;
struct GetFileInfoParams destInfo;
size_t n;
char buf[BF_SIZ];
size_t bytesRead;

void main(void)
{
    atexit(cleanup);

    if (! inputFileName("Source file or directory:", srcName, 
        sizeof(srcName), &srcInfo))
        return;

    if (! inputFileName("Destination file or directory:", destName, 
        sizeof(destName), &destInfo))
        return;

    src = openFile(srcName, "r");

    if (isDirectory(&destInfo))
        concatPath(destName, basename(srcName));

    dest = openFile(destName, "w");

    while ((bytesRead = fread(buf, 1, sizeof(buf), src)) == BF_SIZ)
        if (fwrite(buf, 1, bytesRead, dest) < bytesRead) {
            perror(destName);
            break;
        }

    if (bytesRead > 0 && !feof(dest) && !ferror(dest))
        if (fwrite(buf, 1, bytesRead, dest) < bytesRead)
            perror(destName);

    cleanup();
}

FILE *openFile(const char *name, const char *mode)
{
    FILE *f;
    f = fopen(name, "r");
    if (f == NULL) {
        perror(name);
        exit(EXIT_FAILURE);
    }
    return f;
}

void closeFile(FILE *f, const char *name)
{
    if (f != NULL) {
        if (fclose(f) == EOF) {
            perror(name);
        }
    }
}

void concatPath(char *dest, const char *src)
{
    size_t n;

    n = PRODOS_PATH_MAX - strlen(dest);
    strncat(dest, src, n);
    dest[PRODOS_PATH_MAX] = '\0';
}

void cleanup(void)
{
    closeFile(dest, destName);
    closeFile(src, srcName);
}

