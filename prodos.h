#ifndef PRODOS_MLI_H
#define PRODOS_MLI_H

#include <stdint.h>

/* PATH_MAX POSIX constant
   ProDOS has a 64 char prefix that can be combined with partial
   pathname of 64 characters. This is a total of 128 characters. */
#define PRODOS_PATH_MAX 128

#define PRODOS_FILE_NAME_MAX 15

#define PRODOS_E_IO_ERROR 0x27
#define PRODOS_E_INVALID_PATH_SYNTAX 0x40
#define PRODOS_E_PATH_NOT_FOUND 0x44
#define PRODOS_E_VOLUME_DIR_NOT_FOUND 0x45
#define PRODOS_E_FILE_NOT_FOUND 0x46
#define PRODOS_E_INCOMPAT_FILE_FORMAT 0x4A
#define PRODOS_E_UNSUP_STORAGE_TYPE 0x4B
#define PRODOS_E_INVALID_VALUE_IN_PARAM 0x53
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

