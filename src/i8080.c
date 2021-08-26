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
	uint8_t opcode = state->memory[state->pc];
	
	switch (opcode) {
	case 0x00: // NOP
		// does nothing
		break;
		
	default:   // opcode is undefined
		unimplemented_instruction(state);
		break;
	}

	state->pc++;
}
