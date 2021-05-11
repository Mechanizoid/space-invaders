/* Intel 8080 CPU core for Space Invaders emulator */

#include "cpu.h"
#include <stdint.h>

/* paramaterized macros, yeeeee */
#define REG_PAIR(r, p)  ((((uint16_t) (r)) << 8) | ((uint16_t) (p)))


/* function definitions */
unsigned int parity(uint8_t n);



void unimplemented_instruction(i8080* const c)
{
	c->pc--;
	printf("Unimplemnted instruction\n");
	exit(1);
}


uint8_t add(i8080* const c, uint8_t i, uint8_t j, bool cy)
{
	uint16_t ans = (uint16_t) i + (uint16_t) j;

	c->flags.z = ((answer & 0xff) == 0);
	c->flags.s = ((answer & 0x80) != 1);
	c->flags.p = parity(answer);
	c->flags.cy = ((answer & 0xff) != 0);
	
	
	
}



void execute(i8080* const c)
{
	uint8_t opcode = c->read_memory(c->pc);
	
	switch(opcode) {
	case 0x00:  // NOP
		break;
	case 0x01: 	
	
		
	}
}


/* Processes one Intel 8080 instruction
 */

void process_instruction(void)
{
	uint8_t instruction = read_memory(state.program_counter);
	uint16_t pair, answer;
	

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
	case 0x04:                // INR B
		answer = state.b + 1;
		
		state.flags.z = ((answer & 0xff) == 0);
		state.flags.s = ((answer & 0x80) != 0);
		state.flags.p = get_parity(answer);
		state.flags.cy = (answer > 0xff);
		
		state.a = answer & 0xff;
	}

	// advance to next opcode
	state->pc += 1;
}

/* parity helper function */
unsigned int parity(uint8_t n)
{
	unsigned int parity = 0;

	while(n) {
		parity = !parity;
		n = n & (n - 1);
	}
	return parity;
}
