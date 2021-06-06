#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

/* Type Declarations */
typedef struct Flags {
	// Zero, Sign, Parity, Carry, Auxiliary Carry flags
	uint8_t z:1, s:1, p:1, cy:1, ac:1, pad: 3;
} Flags;

/* struct containing Intel 8080 state and interface to rest of hardware */
typedef struct i8080 {
	/* Intel 8080 state */
	uint16_t pc, sp;              // program counter, stack pointer
	uint8_t a;                    // accumulator
	uint8_t b, c, d, e, h, l;     // Register pairs

	Flags flags;

	/* interface to hardware busses for cpu */
	uint8_t (*read_memory)(uint16_t address);
	void (*write_memory)(uint16_t address, uint8_t data);
	uint8_t (*read_port)(uint8_t port);
	void (*write_port)(uint8_t port, uint8_t data);
} i8080;


/* callable functions exposed to rest of program */
void execute(i8080* const state);

#endif
