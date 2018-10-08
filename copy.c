#include <stdio.h>
#include <stdbool.h>

#include "fileinfo.h"
#include "prodos.h"
#include "cui.h"

char sourceName[PRODOS_PATH_MAX + 1];
char destName[PRODOS_PATH_MAX + 1];
FILE *sourceFile;
FILE *destFile;
struct FileInfo sourceInfo;
struct FileInfo destInfo;

void main(void)
{
    inputFileName("Source file or directory:", sourceName, sizeof(sourceName), &sourceInfo);
    inputFileName("Destination file or directory:", destName, sizeof(destName), &destInfo);

    sourceFile = fopen(sourceName, "r");
    destFile = fopen(destName, "r");
}


