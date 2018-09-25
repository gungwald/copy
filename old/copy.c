#include <stdio.h>  /* FILENAME_MAX */
#include <string.h> /* strerror */
#include <errno.h>  /* errno */
#include "prodos.h" /* prodosGetFileInfo, prodosSetFileInfo */

void copy(const char *srcName, const char *dstName);

#define BUFFER_SIZE 2048

char src[FILENAME_MAX];
char dst[FILENAME_MAX];
char buf[BUFFER_SIZE];

struct ProdosFileInfo fileAttributes;
struct ProdosPathName srcPathName;
struct ProdosPathName dstPathName;

void main(void)
{
    printf("Source file:");
    fgets(src, FILENAME_MAX, stdin);
    printf("Destination file:");
    fgets(dst, FILENAME_MAX, stdin);

    copy(src, dst);
}

void copy(const char *srcName, const char *dstName)
{
    FILE *src, *dst;
    size_t readCount;
    int errorCode;

    fileAttributes.paramCount = PRODOS_GET_FILE_INFO_PARAM_COUNT;
    fileAttributes.pathName = prodosAssignPathName(&srcPathName, srcName);
    errorCode = prodosGetFileInfo(&fileAttributes);
    if (errorCode > 0) {
        fprintf(stderr, "%s: %s\n", srcName, prodosGetMessage(errorCode));
        return;
    }
    
    src = fopen(srcName, "r");
    dst = fopen(dstName, "w");

    while ((readCount = fread(buf,1,BUFFER_SIZE,src)) == BUFFER_SIZE) {
        fwrite(buf,1,BUFFER_SIZE,dst);
    }
    if (feof(src) && readCount > 0) {
        fwrite(buf,1,readCount,dst);
    } else if (ferror(src)) {
        fprintf(stderr, "%s: %s\n", srcName, strerror(errno));
    }
    fclose(dst);
    fclose(src);

    fileAttributes.paramCount = PRODOS_SET_FILE_INFO_PARAM_COUNT;
    fileAttributes.pathName = prodosAssignPathName(&dstPathName, dstName);
    errorCode = prodosSetFileInfo(&fileAttributes);
    if (errorCode > 0) {
        fprintf(stderr, "%s: %s\n", dstName, prodosGetMessage(errorCode));
        return;
    }
}
