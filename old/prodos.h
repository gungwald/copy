#ifndef PRODOS
#define PRODOS

#include <stdint.h> /* uint8_t, uint16_t */

#define PRODOS_GET_FILE_INFO_PARAM_COUNT 0x0a
#define PRODOS_SET_FILE_INFO_PARAM_COUNT 0x07
#define PRODOS_MAX_PATHNAME_LENGTH 64

#define PRODOS_MAX_VOLUME_NAME_LEN 15
#define PRODOS_MAX_VOLUME_COUNT 16

enum ProdosErrorCode {
    PRODOS_ERR_NO_ERROR = 0,
    PRODOS_ERR_BAD_SYS_CALL_NUM = 1,
    PRODOS_ERR_BAD_PARAM_COUNT = 4,
    PRODOS_ERR_INTR_VECT_TBL_FULL = 25,
};

struct ProdosVolume {
    uint8_t drive;
    uint8_t slot;
    uint8_t nameLength;
    char name[PRODOS_MAX_VOLUME_NAME_LEN+1];
};

struct ProdosVolumes {
    uint8_t count;
    struct ProdosVolume volumes[PRODOS_MAX_VOLUME_COUNT];
};

struct ProdosPathName 
{
    uint8_t length;
    char name[PRODOS_MAX_PATHNAME_LENGTH];
};

struct ProdosFileInfo
{
    uint8_t paramCount;
    struct ProdosPathName *pathName;
    uint8_t access;
    uint8_t fileType;
    uint16_t auxType;
    uint8_t storageType;
    uint16_t blocksUsed;
    uint16_t modDate;
    uint16_t modTime;
    uint16_t createDate;
    uint16_t createTime;
};

extern int __fastcall__
prodosGetFileInfo(struct ProdosFileInfo *fileInfo);

extern int __fastcall__
prodosSetFileInfo(struct ProdosFileInfo *fileInfo);

extern struct ProdosPathName *
prodosAssignPathName(struct ProdosPathName *dest, const char *src);

extern char *
prodosGetMessage(enum ProdosErrorCode code);

#endif

