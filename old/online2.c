#include <stdio.h>
#include <stdint.h>

#define PRODOS_MLI 0xbf00
#define ON_LINE (uint8_t) 0xc5
#define PRODOS_NAME_CAPACITY 16

struct OnlineArguments {
    uint8_t argumentCount;
    uint8_t unitNumber;
    char **volumes;
};

struct OnlineArguments arguments;
char volumes[16][PRODOS_NAME_CAPACITY];
uint8_t argumentsAddrLowByte;
uint8_t argumentsAddrHighByte;

void online(void)
{
    arguments.argumentCount = 2;
    arguments.unitNumber = 0; // All units
    arguments.volumes = volumes;

    __asm__(".byte 1");
    __asm__("lda #%b", ON_LINE);
    __asm__("sta %g", l1);
    
    argumentsAddrLowByte = (uint8_t) &arguments;
    argumentsAddrLowByte = (uint8_t) &arguments >> 4;

    __asm__("lda %v", argumentsAddrLowByte);
    __asm__("sta %g", l2);

    __asm__("lda %v", argumentsAddrHighByte);
    __asm__("sta %g", l3);
    
    __asm__("jsr %w", PRODOS_MLI);
l1:
    __asm__("nop");
l2:
    __asm__("nop");
l3:
    __asm__("nop");
    __asm__("bne %g", errorHandler);

errorHandler:
    fprintf(stderr, "Online system call failed\n");
}

void main(void)
{
    online();
    puts(volumes[0]);
}

