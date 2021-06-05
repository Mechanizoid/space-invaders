/* Invaders: An emulator for the original Space Invaders */

#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* global variables */
uint8_t memory[0x10000];


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
	i8080 cpu;

	// initialize i8080
	cpu.read_memory = read_memory;
	cpu.write_memory = write_memory;
	cpu.read_port = read_port;
	cpu.write_port = write_port;

	load_ROM();

	for ( ; ; ) {
		execute(&cpu);
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


size_t open_file(char *name, uint8_t **b)
{
	size_t n = 0;
	FILE *fp = NULL;

	fp = fopen(name, "rb");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open %s\n", name);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	n = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	*b = malloc(n);
	if(NULL == *b) {
		fprintf(stderr, "Call of malloc() failed in open_file()\n");
		exit(1);
	}

	fread(*b, n, 1, fp);
	fclose(fp);

	return n;
}


void load_ROM(void)
{
	uint8_t *b = NULL;
	int n, i;

	n = open_file("roms/invaders.h", &b);
	for(i = 0; i < n; i++) {
		memory[i] = b[i];
	}
	free(b);

	n = open_file("roms/invaders.g", &b);
	for(i = 0; i < n; i++) {
		memory[i + 0x0800] = b[i];
	}
	free(b);

	n = open_file("roms/invaders.f", &b);
	for(i = 0; i < n; i++) {
		memory[i + 0x1000] = b[i];
	}
	free(b);

	n= open_file("roms/invaders.e", &b);
	for(i = 0; i < n; i++) {
		memory[i + 0x1800] = b[i];
	}
	free(b);	
}



uint8_t read_memory(uint16_t address)
{
	return memory[address];
}

void write_memory(uint16_t address, uint8_t data)
{
	// RAM begins at $2000
	if (data > 0x2000)
		memory[address] = data;
}

uint8_t read_port(uint8_t port)
{
	printf("ROM tried to read port %2.2X\n", port);
	exit(0);
}

void write_port(uint8_t port, uint8_t data)
{
	printf("ROM tried to write %2.2X to port %2.2X\n", port, data);
	exit(0);
}
