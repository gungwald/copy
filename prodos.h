#ifndef PRODOS_MLI_H
#define PRODOS_MLI_H

#include <stdint.h>

#define PRODOS_FILE_NAME_MAX 15

#define PRODOS_E_NONE 0x00
#define PRODOS_E_BAD_SYS_CALL_NUM 0x01
#define PRODOS_E_BAD_SYS_PARAM_COUNT 0x04
#define PRODOS_E_INTERRUPT_VECTOR_TABLE_FULL 0x25
#define PRODOS_E_IO_ERROR 0x27
#define PRODOS_E_NO_DEVICE 0x28
#define PRODOS_E_DISK_WRITE_PROTECTED 0x2b
#define PRODOS_E_DISK_SWITCHED 0x2e
#define PRODOS_E_INVALID_PATH_SYNTAX 0x40
#define PRODOS_E_FILE_CTRL_BLK_TABLE_FULL 0x42
#define PRODOS_E_INVALID_REF_NUM 0x43
#define PRODOS_E_PATH_NOT_FOUND 0x44
#define PRODOS_E_VOLUME_DIR_NOT_FOUND 0x45
#define PRODOS_E_FILE_NOT_FOUND 0x46
#define PRODOS_E_DUPLICATE_FILE_NAME 0x47
#define PRODOS_E_OVERRUN_ERROR 0x48
#define PRODOS_E_VOLUME_DIR_FULL 0x49
#define PRODOS_E_INCOMPATIBLE_FILE_FORMAT 0x4A
#define PRODOS_E_UNSUPPORTED_STORAGE_TYPE 0x4B
#define PRODOS_E_END_OF_FILE 0x4C
#define PRODOS_E_POSITION_OUT_OF_RANGE 0x4D
#define PRODOS_E_ACCESS_ERROR 0x4E
#define PRODOS_E_FILE_IS_OPEN 0x50
#define PRODOS_E_DIR_COUNT_ERROR 0x51
#define PRODOS_E_NOT_PRODOS_DISK 0x52
#define PRODOS_E_INVALID_PARAM 0x53
#define PRODOS_E_VOLUME_CTRL_BLK_TABLE_FULL 0x55
#define PRODOS_E_BAD_BUFFER_ADDR 0x56
#define PRODOS_E_DUPLICATE_VOLUME 0x57
#define PRODOS_E_BITMAP_ADDR_IMPOSSIBLE 0x5A

#define GET_FILE_INFO_PARAM_COUNT 0x0a
#define ON_LINE_PARAM_COUNT 0x02
#define ON_LINE_VOLUME_SIZE 256

struct GetFileInfoParams 
{
    uint8_t  param_count;   /* in */
    const char *pathname;   /* in */
    uint8_t  access;        /* out */
    uint8_t  file_type;     /* out */
    uint16_t aux_type;      /* out */
    uint8_t  storage_type;  /* out */
    uint16_t blocks_used;   /* out */
    uint16_t mod_date;      /* out */
    uint16_t mod_time;      /* out */
    uint16_t create_date;   /* out */
    uint16_t create_time;   /* out */
};

struct OnLineParams 
{
    uint8_t param_count;
    uint8_t unit_num;
    char data_buffer[ON_LINE_VOLUME_SIZE];
};

uint8_t on_line(struct OnLineParams *params);
uint8_t get_file_info(struct GetFileInfoParams *params);

#endif

