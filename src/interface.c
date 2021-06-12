/* Interfacing the 8080 emulator with memory and IO */

#include "interface.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>


/* global variables */
uint8_t memory[0x10000];


/* interfacde function declarations */
uint8_t read_memory(uint16_t address);
void write_memory(uint16_t address, uint8_t data);
uint8_t read_port(uint8_t port);
void write_port(uint8_t port, uint8_t data);
void load_ROM(void);



i8080* invaders_init(void)
{
	i8080 *new = NULL;

	new = malloc(sizeof(i8080));
	if (NULL == new) {
		fprintf(stderr, "Call of malloc failed in invaders_initialize()\n");
		exit(1);
	}

	load_ROM();

	new->read_memory = read_memory;
	new->write_memory = write_memory;
	new->read_port = read_port;
	new->write_port = write_port;

	return new;
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

	n = open_file("spaceinv/invaders.h", &b);
	for(i = 0; i < n; i++) {
		memory[i] = b[i];
	}
	free(b);

	n = open_file("spaceinv/invaders.g", &b);
	for(i = 0; i < n; i++) {
		memory[i + 0x0800] = b[i];
	}
	free(b);

	n = open_file("spaceinv/invaders.f", &b);
	for(i = 0; i < n; i++) {
		memory[i + 0x1000] = b[i];
	}
	free(b);

	n= open_file("spaceinv/invaders.e", &b);
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
