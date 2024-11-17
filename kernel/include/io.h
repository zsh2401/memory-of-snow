/**
 * @file io.h
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
#ifndef __IO_H
#define __IO_H
#include <error.h>
extern error_t OutByte(uint16_t port, uint8_t data);
extern error_t InByte(uint16_t port, uint8_t *data);
extern error_t InWord(uint16_t port, uint16_t *data);
#endif //
