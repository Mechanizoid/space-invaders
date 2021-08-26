/* disassembler for i8080 */
#include "dis8080.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int main(int argc, char **argv)
{
	int fsize = 0;
	FILE *fp;
	uint8_t *buf;
	int pc = 0;
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		fprintf(stderr, "ERROR: couldn't open %s\n", argv[1]);
		exit(1);
	}

	/* get the size of the file and read it into buffer */
	fseek(fp, 0L, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buf = malloc(fsize);

	if (buf == NULL) {
		fprintf(stderr, "ERROR: failed to allocate memory for code buffer\n");
		exit(1);
	}

	fread(buf, fsize, 1, fp);
	fclose(fp);


	while (pc < fsize) {
		pc += disassemble8080(buf, pc);
		printf("\n");
	}

	free(buf);
	
	return 0;
}
