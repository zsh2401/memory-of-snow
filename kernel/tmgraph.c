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
static int32_t __width = 80;
static CursorInfo __cinf;

error_t TMG_Init(void *videoMemoryAddress)
{
    __vm = (uint8_t *)videoMemoryAddress;
    __width = 80;

    __cinf.start = 14;
    __cinf.end = 15;
    __cinf.position = 0;
    __cinf.visibility = TRUE;

    byte_t low;
    byte_t high;

    OutByte(0x3D4, 0x0F);
    InByte(0x3D5, &low);

    OutByte(0x3D4, 0x0E);
    InByte(0x3D5, &high);

    __cinf.position = (((uint16_t)high) << 8) | low;

    return F_OK;
}
error_t TMG_Put(int32_t position, char c, byte_t foreground, byte_t background)
{
    if (position < 0 || position > CHARS)
    {
        return F_ERROR_INDEX_OUT_OF_RANGE;
    }
    __vm[position * 2] = c;
    __vm[position * 2 + 1] = (background << 4) | (foreground & 0x0F);
    return F_OK;
}
error_t TMG_Clear()
{
    for (size_t i = 0; i < SIZE; i++)
    {
        __vm[i * 2] = 0;
        __vm[i * 2 + 1] = DEFAULT_ATTR;
    }

    CursorInfo cinf;
    TMG_GetCursor(&cinf);
    cinf.position = 0;
    TMG_SetCursor(cinf);

    return F_OK;
}
error_t TMG_SetCursor(CursorInfo updated)
{
    if (updated.position < 0 || updated.position > CHARS)
    {
        return F_ERROR_INDEX_OUT_OF_RANGE;
    }

    OutByte(0x03d4, 0x0f);
    OutByte(0x03d5, (uint8_t)(updated.position & 0xff));
    OutByte(0x03d4, 0x0e);
    OutByte(0x03d5, (uint8_t)(updated.position >> 8 & 0xff));

    if (updated.visibility)
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

    __cinf = updated;

    return F_OK;
}
error_t TMG_GetCursor(CursorInfo *result)
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

    *result = __cinf;
    return F_OK;
}
error_t TMG_MoveCursor(int32_t delta)
{
    CursorInfo cursor;
    TMG_GetCursor(&cursor);
    cursor.position += delta;
    if (cursor.position < 0)
    {
        cursor.position = 0;
    }
    else if (cursor.position > CHARS)
    {
        cursor.position = CHARS;
    }
    TMG_SetCursor(cursor);
    return F_OK;
}
error_t TMG_GetWidth(int32_t *width)
{
    *width = __width;
    return F_OK;
}
error_t TMG_MoveLine(int32_t delta, bool_t resetToStart)
{
    CursorInfo cursor;
    int32_t width;
    TMG_GetCursor(&cursor);
    TMG_GetWidth(&width);
    cursor.position += delta * width;
    if (resetToStart)
    {
        cursor.position -= cursor.position % width;
    }
    TMG_SetCursor(cursor);
}
error_t TMG_Printf(char *fmt)
{
    CursorInfo cinf;
    int32_t width;

    TMG_GetCursor(&cinf);
    TMG_GetWidth(&width);
    
    for (int32_t i = 0; fmt[i] != 0; i++)
    {
        char current = fmt[i];
        switch (current)
        {
        case '\b':
            TMG_Put(--cinf.position, 0, TM_WHITE, TM_BLACK);
            break;
        case '\n':
        case '\r':
            cinf.position += 80;
            // cinf.position = width * ((cinf.position / width) + 1);
            break;
        default:
            TMG_Put(cinf.position++, current, TM_WHITE, TM_BLACK);
            break;
        }
    }
    TMG_SetCursor(cinf);
    return F_OK;
}