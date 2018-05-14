#include <stdint.h>

#define PRODOS_MLI 0xbf00
#define ON_LINE_SYSTEM_CALL 0xc5
#define PRODOS_FILE_NAME_MAX_LEN 15
typedef char ProdosFileName[PRODOS_FILE_NAME_MAX_LEN + 1];
typedef ProdosFileName ProdosFileNameArray16[16];
typedef struct OnlineSystemCallArguments {
    uint8_t argumentCount;
    uint8_t unitNumber;
    ProdosFileNameArray16 *volumesOutputBuffer;
} OnlineSystemCallArguments;

static ProdosFileNameArray16 volumes;
static OnlineSystemCallArguments arguments;

ProdosFileNameArray16 *online(uint8_t *errorCode)
{
    arguments.argumentCount = 2;
    arguments.unitNumber = 0; // All units
    arguments.volumesOutputBuffer = &volumes;
    
    __asm__("jsr %w", PRODOS_MLI);
    __asm__("db  %b", ON_LINE_SYSTEM_CALL);
    __asm__("da  %v", &arguments);
    __asm__("bne %g", errorHandler);

    return &volumes;

errorHandler:
    return errorCode;
}

