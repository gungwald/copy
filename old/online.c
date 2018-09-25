#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <device.h>
#include "prodos.h"

extern uint8_t onlineVols[];
extern uint8_t onlineSysCall();

enum ProdosErrorCode online(struct ProdosVolumes *vols)
{
    uint8_t byte;
    uint8_t i;
    uint8_t nameLength;
    enum ProdosErrorCode errorCode;
    struct ProdosVolume *volume;

    errorCode = onlineSysCall();
    if (errorCode != PRODOS_ERR_NO_ERROR) {
        return NULL;
    }

    for (i = 0; i < PRODOS_MAX_VOLUME_COUNT; ++i) {
        byte = onlineVols[i*16];
        if (byte == 0) {
            vols->count = i;
            break;
        }
        volume = &(vols->volumes[i]);
        volume->drive = ((byte & 0x80) >> 7) + 1;
        volume->slot = (byte & 0x70) >> 4;  
        nameLength = byte & 0x0f;
        strncpy(volume->name, &(onlineVols[i*16+1]), nameLength);
        volume->name[nameLength] = '\0';
    }
    return errorCode;
}

struct ProdosVolume volume;
struct ProdosVolumes volumes;
enum ProdosErrorCode errorCode;

void printOnline(void)
{
    uint8_t i, dev;
    char volName[FILENAME_MAX];
    
    errorCode = online(&volumes);
    if (errorCode > 0) {
        printf("Error: %d\n", errorCode);
        exit(1);
    }

    for (i = 0; i < volumes.count; ++i) {
        volume = volumes.volumes[i];
        if (strlen(volume.name)>0) {
            printf("S%d,D%d /%s\n", volume.slot, volume.drive, volume.name);
        }
    }

    dev = getfirstdevice();
    while (dev != INVALID_DEVICE) {
        getdevicedir(dev, volName, sizeof(volName));
        printf("device=%d volume=%s\n", dev, volName);
        dev = getnextdevice(dev);
    }
}

