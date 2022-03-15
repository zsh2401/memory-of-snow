/**
 * @file error.h
 * @author Seymour Zhang (zsh2401@gmail.com)
 * @brief Defines errors.
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ERROR_H
#define __ERROR_H
#include "types.h"
typedef uint32_t error_t;
#define F_OK 0
#define F_ERROR 1
#define F_ERROR_KEY_NOT_FOUND 127
#define F_ERROR_INVALID_ADDRESS 128
#define F_ERROR_RUN_OUT_OF_MEMORY 129
#define F_ERROR_STACK_OVER_FLOW 130
#define F_ERROR_INVALID_TARGET_STATE 131
#define F_ERROR_INVALID_OPERATION 132
#define F_ERROR_ACCESS_DENIED 133
#define F_ERROR_SERVICE_UNREACHABLE 134
#define F_ERROR_RESOURCE_NOT_FOUND 135
#define F_ERROR_TARGET_NOT_FOUND 136
#define F_ERROR_CONTAINS_MORE_INFORMATION 137
#define F_ERROR_FATAL 138
#define F_ERROR_DEVICE_FATAL 139
#define F_ERROR_SEGMENTATION_FAULT 140
#define F_ERROR_INVALID_ARGUMENT 141
#define F_ERROR_INDEX_OUT_OF_RANGE 142
#define F_ERROR_NOT_IMPLEMENTED 143
#endif // !__ERROR_H
