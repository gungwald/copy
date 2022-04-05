#include <stdio.h>      /* fopen, fread, fwrite, fclose, FILENAME_MAX */
#include <stdbool.h>
#include <stdlib.h>     /* atexit */
#include <string.h>
#include <apple2.h>	/* _filetype, _auxtype */
#include "libgen.h"	/* basename */

#include "prodos.h"
#include "prodosext.h"
#include "io.h"

#define COPY_BUF_SIZ 2048

enum Status {SUCCESS, FAILURE};

static void cleanup(void);
static FILE *openFile(const char *name, const char *mode);
static void closeFile(FILE *f, const char *name);
static void concatPath(char *accum, const char *src);
static void copyFile(FILE *src, FILE *dest);

FilePath srcName;
FilePath destName;
FILE *src = NULL;
FILE *dest = NULL;
struct GetFileInfoParams srcInfo;
struct GetFileInfoParams destInfo;
size_t n;
char buf[BUF_SIZ];
size_t bytesRead;
uint8_t result;

void main(void)
{
    atexit(cleanup);

    if (! inputFileName("Source file:", srcName))
        return;

    if (! inputFileName("Destination file or directory:", destName))
        return;

    if ((result = getFileInfo(srcName, srcInfo)) != PRODOS_E_NONE) {
        fprintf(stderr, "%s: %s (code %d)\n", srcName, getMessage(result), result);
	return;
    }

    if ((result = getFileInfo(destName, destInfo)) != PRODOS_E_NONE) {
        fprintf(stderr, "%s: %s (code %d)\n", srcName, getMessage(result), result);
	return;
    }

    if (isDirectory(&destInfo))
        concatPath(destName, basename(srcName));

    _filetype = srcInfo->file_type;
    _auxtype = srcInfo->aux_type;

    copyFile(openFile(srcName, "r"), openFile(destName, "w"));
    cleanup();
}

FILE *openFile(const char *name, const char *mode)
{
    FILE *f;
    f = fopen(name, "r");
    if (f == NULL) {
        perror(name);
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

void copyFile(FILE *src, FILE *dest)
{
    if (src == NULL || dest == NULL)
	return;

    while ((bytesRead = fread(buf, 1, sizeof(buf), src)) == COPY_BUF_SIZ)
        if (fwrite(buf, 1, bytesRead, dest) < bytesRead) {
            perror(destName);
            break;
        }

    if (bytesRead > 0 && !feof(dest) && !ferror(dest))
        if (fwrite(buf, 1, bytesRead, dest) < bytesRead)
            perror(destName);
}

