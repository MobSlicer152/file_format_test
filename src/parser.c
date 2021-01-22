#include "parser.h"

struct file_data_map_ent *parse_map_ent(FILE *fp)
{
	struct file_data_map_ent *data_map_ent;
	size_t size = 0;
	uint i;

	/* Ensure we have a valid file pointer */
	assert(fp);

	/* Now allocate the struct */
	data_map_ent = (struct file_data_map_ent *)calloc(1, sizeof(struct file_data_map_ent));
	assert(data_map_ent);

	/* Check whether we should stop parsing */
	fread(&data_map_ent->is_end, sizeof(ubyte), 1, fp);
	if (data_map_ent->is_end)
		return NULL;

	/* Read the data type */
	fread(&data_map_ent->data_type, sizeof(ubyte), 1, fp);
	assert(data_map_ent->data_type > 0 && data_map_ent->data_type < 4);
	printf("data_type: %d ", data_map_ent->data_type);

	switch (data_map_ent->data_type) {
	case DATA_TYPE_ASCII:
		printf("(ASCII)\n");
		break;
	case DATA_TYPE_UNICODE:
		printf("(Unicode)\n");
		break;
	case DATA_TYPE_INT:
		printf("(integer)\n");
		break;
	}

	/* Read the data length */
	fread(&data_map_ent->len, sizeof(size_t), 1, fp);
	assert(data_map_ent->len > 0);
	printf("len: %zu\n", data_map_ent->len);

	/* Determine the size of the data */
	switch (data_map_ent->data_type) {
	case DATA_TYPE_ASCII:
		size = sizeof(char);
		break;
	case DATA_TYPE_UNICODE:
		size = sizeof(wchar_t);
		break;
	case DATA_TYPE_INT:
		size = sizeof(int);
		break;
	}

	/* Now allocate a buffer for the data */
	data_map_ent->data = calloc(data_map_ent->len, size);
	assert(data_map_ent->data);

	/* And read the data */
	fread(data_map_ent->data, size, data_map_ent->len, fp);
	assert(data_map_ent->data);
	
	switch(data_map_ent->data_type) {
	case DATA_TYPE_ASCII:
		printf("data: %s\n", (char *)data_map_ent->data);
		break;
	case DATA_TYPE_UNICODE:
		printf("data: %ls\n", (wchar_t *)data_map_ent->data);
		break;
	case DATA_TYPE_INT:
		printf("data: ");
		for (i = 0; i < data_map_ent->len; i++)
			printf("%X", ((int *)data_map_ent->data)[i]);
		
		printf("\n");
		break;
	}

	printf("\n");

	return data_map_ent;
}

struct file_header *parse_header(FILE *fp)
{
	struct file_header *header;

	/* Ensure we have a valid file pointer */
	assert(fp);

	/* Now allocate the struct */
	header = (struct file_header *)calloc(1, sizeof(struct file_header));
	assert(header);

	/* Check for the magic signature */
	fread(header->magic, sizeof(ubyte), ARRAY_SIZE(header->magic), fp);
	assert(strcmp(header->magic, MAGIC_SIG) == 0);
	printf("magic: %s\n", header->magic);

	/* Get the version */
	fread(&header->version, sizeof(ubyte), 1, fp);
	assert(header->version > 0 && header->version <= FILE_FORMAT_VERSION);
	printf("version: %d\n", header->version);

	/* Get the number of data blocks in the file */
	fread(&header->nblocks, sizeof(size_t), 1, fp);
	assert(header->nblocks > 0);
	printf("nblocks: %d\n", header->nblocks);

	/* Now parse the first data map entry */
	printf("\nData entry 1/%d:\n", header->nblocks);
	header->first = parse_map_ent(fp);

	return header;
}
