#ifndef INTERFACE_H
#define INTERFACE_H

#include "cpu.h"
#include <stdint.h>

/* external functions */
i8080* invaders_init(void);

uint8_t read_memory(uint16_t address);
void write_memory(uint16_t address, uint8_t data);

#endif
