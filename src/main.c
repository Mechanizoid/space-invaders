/* Invaders: An emulator for the original Space Invaders */

#include "i8080.h"
#include "dis8080.h"
#include <stdlib.h>
#include <stdio.h>


#define MEMORY_SIZE 0x10000


uint8_t* initialize_memory(void);
size_t load_rom(uint8_t * buf, const char* const s);



int main(int argc, char **argv)
{
	printf("Hello from space invaders!\n");

	// initialize
	i8080 cpu;

	cpu.pc = 0;
	cpu.memory = initialize_memory();

	for ( ; ; ) {
		execute(&cpu);
	}	

	return 0;
}


uint8_t* initialize_memory(void)
{
	uint8_t *mem = NULL;

	mem = calloc(0x10000, 1);
	if (mem == NULL) {
		fprintf(stderr, "Call of calloc failed in load_rom()");
		exit(EXIT_FAILURE);
	}

	// load roms into appropriate memory locations
	load_rom(&mem[0x0000], "./roms/invaders.h");
	load_rom(&mem[0x0800], "./roms/invaders.g");
	load_rom(&mem[0x1000], "./roms/invaders.f");
	load_rom(&mem[0x1800], "./roms/invaders.e");

	return mem;
}

size_t load_rom(uint8_t * buf, const char* const s)
{
	FILE *fp = NULL;
	int size = 0;
	size_t bytes_written = 0;

	fp = fopen(s, "rb");

	if (fp == NULL) {
		fprintf(stderr, "Failed to open %s\n", s);
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	
	bytes_written = fread(buf, size, 1, fp);
	fclose(fp);

	return bytes_written;
}
