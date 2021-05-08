/* Interfacing the 8080 emulator with memory and IO */

#include "interface.h"
#include "cpu.h"

uint8_t *memory;   // pointer to memory buffer

uint8_t read_memory(uint16_t address)
{
	// to be implemented
	return 0x00;
}

void write_memory(uint16_t address, uint8_t data)
{
	// to be implemented
}
