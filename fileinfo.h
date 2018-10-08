#ifndef MY_FILE_H
#define MY_FILE_H

#include <stdbool.h>
#include "prodos.h"

struct FileInfo
{
    struct GetFileInfoParams infoParams;
    uint8_t getFileInfoResult;
};

extern void initFileInfo(struct FileInfo *f, const char *name);
extern bool isDir(struct FileInfo *f);
extern bool exists(struct FileInfo *f);

#endif

