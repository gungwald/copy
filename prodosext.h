#ifndef PRODOSEXT_H
#define PRODOSEXT_H

#include <stdbool.h>
#include <stdint.h>

extern bool isDirectory(struct GetFileInfoParams *params);
extern const char *getMessage(uint8_t errorCode);

#endif
