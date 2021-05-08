/* Intel 8080 CPU core for Space Invaders emulator */

#include "cpu.h"
#include "interface.h"
#include <stdint.h>


struct Flags {
	uint8_t z : 1;      // Zero flag
	uint8_t s : 1;      // Sign flag
	uint8_t p : 1;      // Parity flag
	uint8_t cy : 1;     // Carry flag
	uint8_t ac : 1;     // Auxiliary carry flag
	uint8_t pad : 3;
};


struct ProcessorState {
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
	uint16_t pc;
	uint16_t sp;
	uint8_t *memory;
	struct Flags flags;
};



void process_instruction(struct ProcessorState *state) {
	uint8_t *instruction = state->memory[state->pc];
	

	switch(instruction) {
	case 0x00:                // NOP
		break;
	case 0x01:                // LXI B, xxxx
		state->b = instruction[2];
		state->c = instruction[1];
		state->pc += 2;
		break;		
	}

	// advance to next opcode
	state->pc += 1;
}
