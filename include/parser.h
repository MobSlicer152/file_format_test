#pragma once

#ifndef PARSER_H
#define PARSER_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>

#include "macro.h"
#include "types.h"

#define MAGIC_SIG "DEMO\0"
#define MAGIC_SIG_LEN 5

#define DATA_TYPE_ASCII 1
#define DATA_TYPE_UNICODE 2
#define DATA_TYPE_INT 3

/**
 * Holds information about a data block in the file.
 */
struct file_data_map_ent {
	ubyte is_end; /**< Whether to stop parsing when this entry is reached */
	ubyte data_type; /**< The type of data */
	size_t len; /**< The length of the data */
	void *data; /**< The data */
	struct file_data_map_ent *next; /**< The next entry */
};

/**
 * Holds the information from the file header.
 */
struct file_header {
	ubyte magic[MAGIC_SIG_LEN]; /**< The signature of the file */
	ubyte version; /**< The version of the file */
	size_t nblocks; /**< The number of data blocks in the file */
	struct file_data_map_ent *first; /**< The first entry in the data map */
};

/**
 * @brief Gets the data map and the associated data.
 * Defined in parser.c
 *
 * @param fp A file pointer at the beginning of
 *  where the start of the data map entry is expected.
 */
struct file_data_map_ent *parse_map_ent(FILE *fp);

/**
 * @brief Parses the header of the file.
 * Defined in parser.c
 *
 * @param fp A file pointer at the beginning of
 *  where the file signature is expected.
 */
struct file_header *parse_header(FILE *fp);

#endif /* !PARSER_H */
