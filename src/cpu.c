/* Intel 8080 CPU core for Space Invaders emulator */

#include "cpu.h"
#include "interface.h"
#include <stdint.h>

/* paramaterized macros, yeeeee */
#define REG_PAIR(r, p)  ((((uint16_t) (r)) << 8) | ((uint16_t) (p)))


struct Flags {
	uint8_t z : 1;      // Zero flag
	uint8_t s : 1;      // Sign flag
	uint8_t p : 1;      // Parity flag
	uint8_t cy : 1;     // Carry flag
	uint8_t ac : 1;     // Auxiliary carry flag
	uint8_t pad : 3;
};


struct ProcessorState {
	uint8_t accumulator;            
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
	uint16_t program_counter;
	uint16_t stack_pointer;
	struct Flags flags;
} state;



void process_instruction(void) {
	uint8_t instruction = read_memory(state.program_counter);
	uint16_t pair;
	

	switch(instruction) {
	case 0x00:                // NOP
		break;
	case 0x01:                // LXI B, D16
		state->b = read_memory(state.program_counter + 2);
		state->c = read_memory(state.program_counter + 1);
		state->pc += 2;
		break;
	case 0x02:                // STAX B
	        pair = ((uint16_t) state.b << 8) | (uint16_t) state.c;
		write_memory(pair, state.a);
		state.program_counter++;
		break;
	case 0x03:                // INX B
		pair = ((uint16_t) state.b << 8) | (uint16_t) state.c;
		pair += 1;
		state.b = (uint8_t) pair >> 8;
		state.c = (uint8_t) (pair ^ 0x00FF);
		break;
	case 0x04:
		
		
			
		
		
	}

	// advance to next opcode
	state->pc += 1;
}
