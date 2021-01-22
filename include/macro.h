#pragma once

#ifndef MACRO_H
#define MACRO_H 1

/**
 * @brief The newest version of the file format
 */
#define FILE_FORMAT_VERSION 1

/**
 * @brief Gets the size of an array
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/**
 * @brief Concatenates two values together
 */
#define CONCAT(hi, lo, type, target) ((target)((hi) << (sizeof(type) << 3) | (type)(lo)))

/**
 * @brief Gets the higher half of a value
 */
#define HIGH(val, target) ((target)((val) >> (sizeof(val) << 3)))

/**
 * @brief Gets the lower half of a value
 */
#define LOW(val, target) ((target)((val) & ((1 << (sizeof(val) << 3)) - 1)))

#endif
