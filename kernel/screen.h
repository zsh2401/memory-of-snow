#ifndef __SCREEN_H
#define __SCREEN_H
#include "kstring.h"
#include "bool.h"
void Screen_Init();
void Screen_Clear();

int32_t Screen_GetLineWidth();
uint32_t Screen_GetCursorPosition();

void Screen_SetCursorPosition(uint32_t abs);
void Screen_Write(kstring_t str);

void Screen_MoveCursor(int32_t delta);
void Screen_MoveCursorToLine(int32_t delta, bool_t moveToStart);
void Screen_MoveCursorToStart();
#endif // !__SCREEN_H
