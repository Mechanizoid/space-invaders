/* Invaders: An emulator for the original Space Invaders */

#include "cpu.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




/* function declarations */
uint8_t read_memory(uint16_t address);
void write_memory(uint16_t address, uint8_t data);
uint8_t read_port(uint8_t port);
void write_port(uint8_t port, uint8_t memory);
size_t open_file(char *name, uint8_t **buf);
void load_ROM(void);
void dump_memory(uint8_t *b, int n);



int main(void)
{
	// set up i8080 state
	i8080 *cpu;

	cpu = invaders_init();

	for ( ; ; ) {
		execute(cpu);
	}
	
	return 0;
}

/* dumps n bytes of buffer to screen */
void dump_memory(uint8_t *b, int n)
{
	int i = 0;

	for ( ; i < n ; i++) {
		if (i % 8 == 0)
			printf("\n%8.8x: ", i);
		printf("%2.2X ", b[i]);
	}
	printf("\n");
}


