/**
 * @file io.c
 * @author Seymour Zhang (zsh2401@gmail.com)
 * @brief Access IO ports.
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 * Functions in this file provides a series
 * of basic C programing API to access
 * ports.
 */
#include "io.h"
error_t OutByte(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(data), "Nd"(port));
    return F_OK;
}
error_t InByte(uint32_t port, uint8_t *data)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    *data = ret;
    return F_OK;
}