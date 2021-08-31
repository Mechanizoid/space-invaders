/* Intel 8080 CPU for Space Invaders Emulator */

#include "i8080.h"
#include "dis8080.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>



const int OP_EXTRA_BYTES[256] = {
	[0x01] = 2, [0x06] = 1, [0x0e] = 1, [0x11] = 2, [0x16] = 1, [0x1e] = 1,
	[0x21] = 2, [0x22] = 2, [0x26] = 1, [0x2a] = 2, [0x2e] = 1, [0x31] = 2,
	[0x32] = 2, [0x36] = 1, [0x3a] = 2, [0x3e] = 1, [0xc2] = 2, [0xc3] = 2,
	[0xc4] = 2, [0xc6] = 1, [0xca] = 2, [0xcb] = 2, [0xcc] = 2, [0xcd] = 2,
	[0xce] = 1, [0xd2] = 2, [0xd3] = 1, [0xd4] = 2, [0xd6] = 1, [0xda] = 2,
	[0xdb] = 1, [0xdc] = 2, [0xdd] = 2, [0xde] = 1, [0xe2] = 2, [0xe4] = 2,
	[0xe6] = 1, [0xea] = 2, [0xec] = 2, [0xed] = 2, [0xee] = 1, [0xef] = 2,
	[0xf2] = 2, [0xf4] = 2, [0xf6] = 1, [0xfa] = 2, [0xfc] = 2, [0xfd] = 2,
	[0xfe] = 1
};


/* Executes one instruction
 */
int execute(i8080 * const state)
{
	uint8_t *opcode = &state->memory[state->pc];
	uint16_t addr, pair;
	int status = 1;
	
	status += OP_EXTRA_BYTES[*opcode];
	
	switch (*opcode) {
	
		/* data transfer group */
	case 0x06: // MVI B D8
		addr = (state->h << 8) | state->l;
		state->memory[addr] = opcode[1];
		break;

	case 0x11: // LXI D
		state->d = opcode[2];
		state->e = opcode[1];
		break;

	case 0x21: // LXI H
		state->h = opcode[2];
		state->l = opcode[1];
		break;
		
	case 0x31: // LXI SP
		state->sp = (opcode[2] << 8) | opcode[1];
		break; 

	case 0x1a: // LDAX D
		addr = (state->d << 8) | state->e;
		state->a = state->memory[addr];
		break;

	case 0x77: // MOV M, A
		addr = (state->h << 8) | state->l;
		state->memory[addr] = state->a;
		break;

		/* arithmetic group */
	case 0x13: // INX D
		pair = (state->h << 8) | state->l;
		pair += 1;
		state->h = pair >> 8;
		state->l = pair & 0x00ff;
		break;
		
	case 0x23: // INX H
		pair = (state->h << 8) | state->l;
		pair += 1;
		state->h = pair >> 8;
		state->l = pair & 0x00ff;
		break;

		/* branch statements */
	case 0xc3: // JMP
		state->pc = (opcode[2] << 8) | opcode[1];
		status = 0;
		break;

	case 0xcd: // CALL
		state->pc += 2;
		state->memory[state->sp - 2] = (state->pc >> 8);
		state->memory[state->sp - 1] = (state->pc & 0x0F);
		state->sp -= 2;
		state->pc = (opcode[2] << 8) | opcode[1];
		status = 0;

		break;

		/* stack, IO, and machine control group */
	case 0x00: // NOP
		// does nothing
		break;
		
	default:   /* unimplemented opcode */
		status = -1;
		break;
	}

	return status;
}
