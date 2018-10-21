#include <stdio.h>      /* fopen, fread, fwrite, fclose */
#include <stdbool.h>
#include <stdlib.h>     /* atexit */

#include "fileinfo.h"
#include "prodos.h"
#include "cui.h"

#define BUFFER_SIZE 2048

void cleanup(void);
FILE *openFile(const char *name, const char *mode);
void closeFile(FILE *f, const char *name);
void concatPath(char *dest, const char *src);

char sourceName[PRODOS_PATH_MAX + 1];
char destName[PRODOS_PATH_MAX + 1];
FILE *sourceFile = NULL;
FILE *destFile = NULL;
struct FileInfo sourceInfo;
struct FileInfo destInfo;
size_t n;
char buffer[BUFFER_SIZE];
size_t bytesRead;

void main(void)
{
    atexit(cleanup);

    inputFileName("Source file or directory:", sourceName, sizeof(sourceName), &sourceInfo);
    inputFileName("Destination file or directory:", destName, sizeof(destName), &destInfo);

    sourceFile = openFile(sourceName, "r");

    if (isDir(&destInfo)) {
        concatPath(destName, basename(sourceName));
    }

    destFile = openFile(destName, "w");

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) == BUFFER_SIZE) {
        if (fwrite(buffer, 1, bytesRead, destFile) < bytesRead) {
            perror(destName);
            break;
        }
    }
    if (bytesRead > 0 && !feof(destFile) && !ferror(destFile)) {
        if (fwrite(buffer, 1, bytesRead, destFile) < bytesRead) {
            perror(destName);
        }
    }
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
    closeFile(destFile, destName);
    closeFile(sourceFile, sourceName);
}

