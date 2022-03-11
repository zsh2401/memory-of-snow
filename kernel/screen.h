#ifndef __SCREEN_H
#define __SCREEN_H
#include "mos.h"

void Screen_Init();
void Screen_Clear();

uint32_t Screen_GetLineWidth();

/**
 * @brief 
 * 
 * @param newValue negative value will be ignorant.
 * @return uint32_t current positon
 */
uint32_t Screen_CursorPosition(int32_t newValue);

void Screen_Write(kstring_t str);

void Screen_MoveCursor(int32_t delta);
void Screen_MoveCursorToLine(int32_t delta, bool_t moveToStart);
void Screen_MoveCursorToStart();
#endif // !__SCREEN_H
