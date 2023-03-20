/* Invaders: An emulator for the original Space Invaders */

#include "i8080.h"
#include "dis8080.h"
#include <stdlib.h>
#include <stdio.h>


#define MEMORY_SIZE 0x10000

/* function declarations */
uint8_t* initialize_memory(void);
size_t load_rom(uint8_t * buf, const char* const s);
void step_through(i8080 * const state);
void unimplemented_instruction(i8080 *state);


int main(int argc, char **argv)
{
	printf("Hello from space invaders!\n");

	// initialize
	i8080 cpu;

	cpu.pc = 0;
	cpu.memory = initialize_memory();

	step_through(&cpu);

	free(cpu.memory);

	return 0;
}


void step_through(i8080 * const state)
{
	int is_running = 1;
	int status = 0;
	char in;

	while(is_running) {
		status = execute(state);

		if (status == -1) {
			unimplemented_instruction(state);
		}
		
		disassemble8080(state->memory, state->pc);
		state->pc += status;

		while((in = getchar())) {
			if (in == '\n') {
				break;
			} else if (in == 'q') {
				is_running = 0;
				break;
			}
		}
	}
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


/* Reports an unimplemented instruction and gives the disassembly
 */
void unimplemented_instruction(i8080 *state) {
	printf("\n************************************************************");
	printf("\nUnimplemented instruction: %2.2X\n",
	       state->memory[state->pc]);
	disassemble8080(state->memory, state->pc);
	printf("\n");
	
	exit(0);
}
