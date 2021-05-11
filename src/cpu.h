#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>


typedef struct Flags {
	// Zero, Sign, Parity, Carry, Auxiliary Carry flags
	uint8_t z:1, s:1, p:1, cy:1, ac:1;
} Flags;


typedef struct i8080 {
	uint16_t pc, sp;              // program counter, stack pointer
	uint8_t a;                    // accumulator
	uint8_t b, c, d, e, h, l;     // Register pairs

	Flags flags;

	/* These function pointers will be initialized to refer to 
	 * functions defined elsewhere that allow the CPU emulation
	 * to address memory or ports.
	 */
	uint8_t (*read_memory)(uint16_t address);
	void (*write_memory)(uint16_t address, uint8_t data);
	uint8_t (*read_port)(uint8_t port);
	void (*write_port)(uint8_t port, uint8_t data)
} i8080;





#endif
