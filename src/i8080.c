/* Intel 8080 CPU for Space Invaders Emulator */

#include "i8080.h"
#include "dis8080.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Reports an unimplemented instruction and gives the disassembly
 */
void unimplemented_instruction(i8080 *state) {
	printf("Unimplemented instruction: %2.2X\n", state->memory[state->pc]);
	disassemble8080(state->memory, state->pc);
	printf("\n");
	
	exit(0);
}

/* Executes one instruction
 */
void execute(i8080 *state)
{
	uint8_t *opcode = &state->memory[state->pc];
	
	switch (*opcode) {
	
		/* data transfer group */
	case 0x31: // LXI
		state->sp = (opcode[2] << 8) | (opcode[1]);
		state->pc += 2;
		break;
		
		/* branch statements */
	case 0xc3: // JMP
		state->pc = (opcode[2] << 8) | (opcode[1]);
		state->pc -= 1;
		
		break;

		/* stack, IO, and machine control group */
	case 0x00: // NOP
		// does nothing
		break;

		
	default:   /* unimplemented opcodes */
		unimplemented_instruction(state);
		break;
	}

	state->pc += 1;
}
