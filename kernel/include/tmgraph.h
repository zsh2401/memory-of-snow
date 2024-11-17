#ifndef __TM_GRAPH_H
#define __TM_GRAPH_H
#include <error.h>
#include <types.h>
#define DEFAULT_ATTR 0b00000111
#define TM_WHITE 0b0111
#define TM_BLACK 0b0000
typedef struct
{
    bool_t visibility;
    int32_t position;
    byte_t start;
    byte_t end;
} CursorInfo;
error_t TMG_Init(void *videoMemoryAddress);
error_t TMG_Put(int32_t position, char c, byte_t foreground, byte_t background);
error_t TMG_SetCursor(CursorInfo updated);
error_t TMG_GetCursor(CursorInfo *result);
error_t TMG_MoveCursor(int32_t delta);
error_t TMG_GetWidth(int32_t *width);
error_t TMG_Printf(const char *fmt, ...);
// error_t TMG_MoveLine(int32_t delta, bool_t resetToStart);
// error_t TextModeGraph_PutString(char *str, byte_t foreground, byte_t background);
// error_t TextModeGraph_PutNumber(int64_t value, int32_t radix, byte_t foreground, byte_t background);
error_t TMG_Clear();
#endif // !