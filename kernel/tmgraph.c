/**
 * @file tmgraph.c
 * @author Seymour Zhang (zsh2401@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 * https://wiki.osdev.org/Text_Mode_Cursor
 */
#include "tmgraph.h"
#include "io.h"
#define SIZE 4096
#define CHARS 2000
static uint8_t *__vm = NULL_PTR;
static int32_t __cursor = 0;
static int32_t __width = 80;
error_t TextModeGraph_Init(void *videoMemoryAddress)
{
    __vm = (uint8_t *)videoMemoryAddress;
    __width = 80;

    byte_t low;
    byte_t high;

    OutByte(0x3D4, 0x0F);
    InByte(0x3D5, &low);

    OutByte(0x3D4, 0x0E);
    InByte(0x3D5, &high);

    __cursor = (((uint16_t)high) << 8) | low;

    return F_OK;
}
error_t TextModeGraph_Put(int32_t position, char c, byte_t foreground, byte_t background)
{
    if (position < 0 || position > CHARS)
    {
        return F_ERROR_INDEX_OUT_OF_RANGE;
    }
    __vm[position * 2] = c;
    __vm[position * 2 + 1] = (background << 4) | (foreground & 0x0F);
    return F_OK;
}
error_t TextModeGraph_Clear()
{
    for (size_t i = 0; i < SIZE; i++)
    {
        __vm[i * 2] = 0;
        __vm[i * 2 + 1] = DEFAULT_ATTR;
    }
    TextModeGraph_SetCursor(0);
    return F_OK;
}
error_t TextModeGraph_SetCursor(int32_t position)
{
    if (position < 0 || position > CHARS)
    {
        return F_ERROR_INDEX_OUT_OF_RANGE;
    }

    OutByte(0x03d4, 0x0f);
    OutByte(0x03d5, (uint8_t)(position & 0xff));
    OutByte(0x03d4, 0x0e);
    OutByte(0x03d5, (uint8_t)(position >> 8 & 0xff));

    __cursor = position;

    return F_OK;
}
error_t TextModeGraph_GetCursor(int32_t *result)
{
    // byte_t low;
    // byte_t high;

    // OutByte(0x3D4, 0x0F);
    // InByte(0x3D5, &low);

    // OutByte(0x3D4, 0x0E);
    // InByte(0x3D5, &high);

    // int16_t fuck = high;
    // fuck <<= 8;
    // *result = fuck | low;

    *result = __cursor;
    return F_OK;
}
error_t TextModeGraph_SetCursorVisibility(bool_t visible)
{
    if (visible)
    {
        byte_t cursor_start = 14;
        byte_t cursor_end = 15;

        byte_t b;
        OutByte(0x3D4, 0x0A);
        InByte(0x3D5, &b);
        OutByte(0x3D5, (b & 0xC0) | cursor_start);

        OutByte(0x3D4, 0x0B);
        InByte(0x3D5, &b);
        OutByte(0x3D5, (b & 0xE0) | cursor_end);
    }
    else
    {
        OutByte(0x3D4, 0x0A);
        OutByte(0x3D5, 0x20);
    }
}
error_t TextModeGraph_MoveCurosr(int32_t delta)
{
    int32_t cursor;
    TextModeGraph_GetCursor(&cursor);
    cursor += delta;
    if (cursor < 0)
    {
        cursor = 0;
    }
    else if (cursor > CHARS)
    {
        cursor = CHARS;
    }
    TextModeGraph_SetCursor(cursor);
    return F_OK;
}
error_t TextModeGraph_PutString(char *str, byte_t foreground, byte_t background)
{
    int32_t cursor;
    int32_t i;

    TextModeGraph_GetCursor(&cursor);

    for (i = 0; str[i] != 0; i++)
    {
        TextModeGraph_Put(cursor + i, str[i], foreground, background);
    }

    TextModeGraph_MoveCurosr(i);
    return F_OK;
}
error_t TextModeGraph_GetWidth(int32_t *width)
{
    *width = __width;
    return F_OK;
}
error_t TextModeGraph_MoveLine(int32_t delta, bool_t resetToStart)
{
    int32_t cursor;
    int32_t width;
    TextModeGraph_GetCursor(&cursor);
    TextModeGraph_GetWidth(&width);
    cursor += delta * width;
    if (resetToStart)
    {
        cursor -= cursor % width;
    }
    TextModeGraph_SetCursor(cursor);
}