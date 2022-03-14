#ifndef  __TEXT_MODE_H
#define __TEXT_MODE_H
#include "../types.h"
typedef void* tty_t;
typedef uint32_t tty_mode;
void TtyCreate(tty_t* tty, tty_mode mode);
void TtyPut(tty_t tty,uint8_t c, uint8_t attr);
void TtySetCursor(tty_t tty, uint32_t position);
void TtyDispose(tty_t tty);
#endif // ! __TEXT_MODE_H