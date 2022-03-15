#ifndef __TM_GRAPH_H
#define __TM_GRAPH_H
#include "error.h"
#define DEFAULT_ATTR 0b00000111
#define TM_WHITE 0b0111
#define TM_BLACK 0b0000
error_t TextModeGraph_Init(void *videoMemoryAddress);
error_t TextModeGraph_Put(int32_t position, char c, byte_t foreground, byte_t background);
error_t TextModeGraph_SetCursor(int32_t position);
error_t TextModeGraph_GetCursor(int32_t *result);
error_t TextModeGraph_MoveCurosr(int32_t delta);
error_t TextModeGraph_GetWidth(int32_t *width);
error_t TextModeGraph_MoveLine(int32_t delta, bool_t resetToStart);
error_t TextModeGraph_SetCursorVisibility(bool_t visible);
error_t TextModeGraph_PutString(char *str, byte_t foreground, byte_t background);
error_t TextModeGraph_PutNumber(int64_t value, int32_t radix, byte_t foreground, byte_t background);
error_t TextModeGraph_Clear();
#endif // !