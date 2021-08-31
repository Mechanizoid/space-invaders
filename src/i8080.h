#ifndef I8080_H
#define I8080_H

#include <stdint.h>

typedef struct Flags {
	uint8_t z:1, s:1, p:1, cy:1, ac:1, pad: 3;
} Flags;

typedef struct i8080 {
	uint16_t pc, sp;              // program counter, stack pointer
	uint8_t a, b, c, d, e, h, l;  // accumlator and register pairs

	Flags flags;

	/* pointer to emulator memory */
	uint8_t *memory;
} i8080;

/* function declarations */
int execute(i8080 * const state);

#endif
