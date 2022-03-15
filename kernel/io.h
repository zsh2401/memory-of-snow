#ifndef __IO_H
#define __IO_H
#include "error.h"
error_t OutByte(uint16_t port, uint8_t data);
error_t InByte(uint32_t port, uint8_t *data);
#endif // !
