#include <apple2_filetype.h>   /* PRODOS_T_DIR */
#include "fileinfo.h"
#include "prodos.h"

static struct GetFileInfoParams *infoParams;

void initFileInfo(struct FileInfo *f, const char *name)
{
    infoParams = &(f->infoParams);
    infoParams->param_count = GET_FILE_INFO_PARAM_COUNT;
    infoParams->pathname = name;
    f->getFileInfoResult = get_file_info(infoParams);
}

bool isDir(struct FileInfo *f)
{
    return f->infoParams.file_type == PRODOS_T_DIR;
}

bool exists(struct FileInfo *f)
{
    if (f->getFileInfoResult == 0)
        return true;
    else
        return false;
}

