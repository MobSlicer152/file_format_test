#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <string.h>

#include "macro.h"
#include "parser.h"
#include "types.h"

int main(int argc, char *argv[])
{
	struct file_header *header;
	struct file_data_map_ent *entry;
	size_t blocks_parsed = 1;
	FILE *fp;

	/* Open our file */
	fp = fopen("file", "rb");
	assert(fp);

	/* Parse the header into the data structure */
	printf("File header:\n");
	header = parse_header(fp);

	/* Now parse the rest of the file */
	entry = header->first;
	while (entry && (blocks_parsed < header->nblocks)) {
		blocks_parsed++;
		printf("Data entry %zu/%zu:\n", blocks_parsed, header->nblocks);
		entry->next = parse_map_ent(fp);
		entry = entry->next;
	}

	/* Close the file */
	fclose(fp);

	int c = getchar();
	return 0;
}
