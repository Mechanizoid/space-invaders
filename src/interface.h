#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdint.h>

/* external functions */
uint8_t read_memory(uint16_t address);
void write_memory(uint16_t address, uint8_t data);

#endif
