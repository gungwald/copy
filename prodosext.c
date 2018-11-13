#include <stdbool.h>
#include <apple2_filetype.h>
#include "prodos.h"
#include "prodosext.h"

bool isDirectory(struct GetFileInfoParams *params)
{
    return params->file_type == PRODOS_T_DIR;
}

const char *getMessage(uint8_t errorCode)
{
    switch (errorCode) {
        case PRODOS_E_NONE:
            return "No error";
        case PRODOS_E_BAD_SYS_CALL_NUM:
            return "Bad system call number";
        case PRODOS_E_BAD_SYS_PARAM_COUNT:
            return "Bad system call parameter count";
        case PRODOS_E_INTERRUPT_VECTOR_TABLE_FULL:
            return "Interrupt vector table full";
        case PRODOS_E_IO_ERROR:
            return "I/O error";
        case PRODOS_E_NO_DEVICE:
            return "No device detected/connected";
        case PRODOS_E_DISK_WRITE_PROTECTED:
            return "Disk is write protected";
        case PRODOS_E_DISK_SWITCHED:
            return "Disk switched";
        case PRODOS_E_INVALID_PATH_SYNTAX:
            return "Invalid path syntax";
        case PRODOS_E_FILE_CTRL_BLK_TABLE_FULL:
            return "File control block table full";
        case PRODOS_E_INVALID_REF_NUM:
            return "Invalid reference number";
        case PRODOS_E_PATH_NOT_FOUND:
            return "Path not found";
        case PRODOS_E_VOLUME_DIR_NOT_FOUND:
            return "Volume directory not found";
        case PRODOS_E_FILE_NOT_FOUND:
            return "File not found";
        case PRODOS_E_DUPLICATE_FILE_NAME:
            return "Duplicate file name";
        case PRODOS_E_OVERRUN_ERROR:
            return "No space left on device";
        case PRODOS_E_VOLUME_DIR_FULL:
            return "No entries left in volume directory";
        case PRODOS_E_INCOMPATIBLE_FILE_FORMAT:
            return "Incompatible file format";
        case PRODOS_E_UNSUPPORTED_STORAGE_TYPE:
            return "Unsupported storage type";
        case PRODOS_E_END_OF_FILE:
            return "End of file reached";
        case PRODOS_E_POSITION_OUT_OF_RANGE:
            return "File position out of range";
        case PRODOS_E_ACCESS_ERROR:
            return "File attribute forbids operation";
        case PRODOS_E_FILE_IS_OPEN:
            return "File is open";
        case PRODOS_E_DIR_COUNT_ERROR:
            return "Directory header / file entry mismatch";
        case PRODOS_E_NOT_PRODOS_DISK:
            "Not a ProDOS disk";
        case PRODOS_E_INVALID_PARAM:
            return "Invalid value in parameter";
        case PRODOS_E_VOLUME_CTRL_BLK_TABLE_FULL:
            return "Volume control block table full";
        case PRODOS_E_BAD_BUFFER_ADDR:
            return "Bad buffer address";
        case PRODOS_E_DUPLICATE_VOLUME:
            return "Duplicate volume";
        case PRODOS_E_BITMAP_ADDR_IMPOSSIBLE:
            return "Bitmap address impossible";
        default:
            return "Unknown error";
    }
}

