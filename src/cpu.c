/* Intel 8080 CPU core for Space Invaders emulator */

#include "cpu.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



/* Helper function declarations */
void unimplemented_instruction(i8080* const c);
static bool parity(const uint8_t n);
static bool carry(const uint8_t a, const uint8_t b, const bool cy);
static void set_ZSP(i8080* const s, const uint8_t result);
static void add(i8080* const c, const uint8_t value, const bool cy);

/* Helper function definitions */

void unimplemented_instruction(i8080* const c)
{
	printf("Unimplemented instruction\n");
	exit(1);
}



/* sets the carry flag */
static bool carry(const uint8_t a, const uint8_t b, const bool cy)
{
	uint16_t result = a + b + cy;
	return result > 0xff;
}

/* sets the Zero, Sign, and Parity flags */
static void set_ZSP(i8080* const c, const uint8_t result)
{
	c->flags.z = result == 0;
	c->flags.s = result >> 7;
	c->flags.p = parity(result);
}


/* parity helper function */
static bool parity(uint8_t n)
{
	bool parity = 0;

	while(n) {
		parity = !parity;
		n = n & (n - 1);
	}
	return parity;
}


/* adds 
 */
static void add(i8080* const c, const uint8_t val, const bool cy)
{
	uint8_t result;

	result = c->a + val + cy;
	c->flags.cy = carry(c->a, val, cy);
	set_ZSP(c, result);

	c->a = result & 0xff;
}

/* subtracts val from the accumulator, with optional carry
 */
static void sub(i8080* const c, const uint8_t val, const bool cy)
{
	uint8_t result;

	result = c->a - (val + cy);

	c->flags.cy = c->a < val;
	set_ZSP(c, result);

	c->a = result;
}


/*----------------------------------------------------------------------------*/
/* API function definitions */


/* Processes one Intel 8080 instruction */
void execute(i8080* const c)
{
	uint8_t instruction; 
	uint16_t pair;
	uint8_t t;

	instruction = c->read_memory(c->pc);
	c->pc++;

	switch(instruction) {
	case 0x00:                // NOP
		break;
	case 0x01:                // LXI B, D16
		unimplemented_instruction(c);
		break;
	case 0x02:                // STAX B
		unimplemented_instruction(c);
		break;
	case 0x03:                // INX B
		unimplemented_instruction(c);
		break;
	case 0x04:                // INR B
		c->b++;
		set_ZSP(c, c->b);
		break;
	case 0x05:
		c->b--;
		set_ZSP(c, c->b);
		break;
	case 0x06: unimplemented_instruction(c); break;
	case 0x07: unimplemented_instruction(c); break;
	case 0x08: unimplemented_instruction(c); break;
	case 0x09: unimplemented_instruction(c); break;
	case 0x0a: unimplemented_instruction(c); break;
	case 0x0b: unimplemented_instruction(c); break;
	case 0x0c:          // INR C
		c->c++;
		set_ZSP(c, c->c);
	case 0x0d:          // DCR C
		c->c--;
		set_ZSP(c, c->c);
		break;
	case 0x0e: unimplemented_instruction(c); break;
	case 0x0f: unimplemented_instruction(c); break;
	case 0x10: unimplemented_instruction(c); break;
	case 0x11: unimplemented_instruction(c); break;
	case 0x12: unimplemented_instruction(c); break;
	case 0x13: unimplemented_instruction(c); break;
	case 0x14:          // INR D
		c->d++;
		set_ZSP(c, c->d);
		break;
	case 0x15:          // DCR D
		c->d--;
		set_ZSP(c, c->d);
		break;
	case 0x16: unimplemented_instruction(c); break;
	case 0x17: unimplemented_instruction(c); break;
	case 0x18:          // *NOP
		unimplemented_instruction(c);
		break;
	case 0x19: unimplemented_instruction(c); break;
	case 0x1a: unimplemented_instruction(c); break;
	case 0x1b: unimplemented_instruction(c); break;
	case 0x1c:          // INR E
		c->e++;
		set_ZSP(c, c->e);
		break;
	case 0x1d:          // DCR E
		c->e--;
		set_ZSP(c, c->e);
		break;
	case 0x1e: unimplemented_instruction(c); break;
	case 0x1f: unimplemented_instruction(c); break;
	case 0x20: unimplemented_instruction(c); break;
	case 0x21: unimplemented_instruction(c); break;
	case 0x22: unimplemented_instruction(c); break;
	case 0x23: unimplemented_instruction(c); break;
	case 0x24:          // INR H
		c->h++;
		set_ZSP(c, c->h);
		break;
	case 0x25:          // DCR H
		c->h--;
		set_ZSP(c, c->h);
		break;
	case 0x26: unimplemented_instruction(c); break;
	case 0x27: unimplemented_instruction(c); break;
	case 0x28: unimplemented_instruction(c); break;
	case 0x29: unimplemented_instruction(c); break;
	case 0x2a: unimplemented_instruction(c); break;
	case 0x2b: unimplemented_instruction(c); break;
	case 0x2c:          // INR L
		c->l++;
		set_ZSP(c, c->l);
		break;
	case 0x2d:          // DCR L
		c->l--;
		set_ZSP(c, c->l);
	case 0x2e: unimplemented_instruction(c); break;
	case 0x2f: unimplemented_instruction(c); break;
	case 0x30: unimplemented_instruction(c); break;
	case 0x31: unimplemented_instruction(c); break;
	case 0x32: unimplemented_instruction(c); break;
	case 0x33: unimplemented_instruction(c); break;
	case 0x34:          // INR M
		pair = (c->h << 8) | (c->l);
		t = c->read_memory(pair);
		t++;
		set_ZSP(c, t);
		c->write_memory(pair, t);
		break;
	case 0x35:          // DCR M
		pair = (c->h << 8) | (c->l);
		t = c->read_memory(pair);
		t--;
		set_ZSP(c, t);
		c->write_memory(pair, t);
		break;
	case 0x36: unimplemented_instruction(c); break;
	case 0x37: unimplemented_instruction(c); break;
	case 0x38: unimplemented_instruction(c); break;
	case 0x39: unimplemented_instruction(c); break;
	case 0x3a: unimplemented_instruction(c); break;
	case 0x3b: unimplemented_instruction(c); break;
	case 0x3c:          // INR A
		c->a = c->a + 1;
		set_ZSP(c, c->a);
		break;
	case 0x3d:          // DCR A
		c->a = c->a - 1;
		set_ZSP(c, c->a);
		break;
	case 0x3e: unimplemented_instruction(c); break;
	case 0x3f: unimplemented_instruction(c); break;
	case 0x40: unimplemented_instruction(c); break;
	case 0x41: unimplemented_instruction(c); break;
	case 0x42: unimplemented_instruction(c); break;
	case 0x43: unimplemented_instruction(c); break;
	case 0x44: unimplemented_instruction(c); break;
	case 0x45: unimplemented_instruction(c); break;
	case 0x46: unimplemented_instruction(c); break;
	case 0x47: unimplemented_instruction(c); break;
	case 0x48: unimplemented_instruction(c); break;
	case 0x49: unimplemented_instruction(c); break;
	case 0x4a: unimplemented_instruction(c); break;
	case 0x4b: unimplemented_instruction(c); break;
	case 0x4c: unimplemented_instruction(c); break;
	case 0x4d: unimplemented_instruction(c); break;
	case 0x4e: unimplemented_instruction(c); break;
	case 0x4f: unimplemented_instruction(c); break;
	case 0x50: unimplemented_instruction(c); break;
	case 0x51: unimplemented_instruction(c); break;
	case 0x52: unimplemented_instruction(c); break;
	case 0x53: unimplemented_instruction(c); break;
	case 0x54: unimplemented_instruction(c); break;
	case 0x55: unimplemented_instruction(c); break;
	case 0x56: unimplemented_instruction(c); break;
	case 0x57: unimplemented_instruction(c); break;
	case 0x58: unimplemented_instruction(c); break;
	case 0x59: unimplemented_instruction(c); break;
	case 0x5a: unimplemented_instruction(c); break;
	case 0x5b: unimplemented_instruction(c); break;
	case 0x5c: unimplemented_instruction(c); break;
	case 0x5d: unimplemented_instruction(c); break;
	case 0x5e: unimplemented_instruction(c); break;
	case 0x5f: unimplemented_instruction(c); break;
	case 0x60: unimplemented_instruction(c); break;
	case 0x61: unimplemented_instruction(c); break;
	case 0x62: unimplemented_instruction(c); break;
	case 0x63: unimplemented_instruction(c); break;
	case 0x64: unimplemented_instruction(c); break;
	case 0x65: unimplemented_instruction(c); break;
	case 0x66: unimplemented_instruction(c); break;
	case 0x67: unimplemented_instruction(c); break;
	case 0x68: unimplemented_instruction(c); break;
	case 0x69: unimplemented_instruction(c); break;
	case 0x6a: unimplemented_instruction(c); break;
	case 0x6b: unimplemented_instruction(c); break;
	case 0x6c: unimplemented_instruction(c); break;
	case 0x6d: unimplemented_instruction(c); break;
	case 0x6e: unimplemented_instruction(c); break;
	case 0x6f: unimplemented_instruction(c); break;
	case 0x70: unimplemented_instruction(c); break;
	case 0x71: unimplemented_instruction(c); break;
	case 0x72: unimplemented_instruction(c); break;
	case 0x73: unimplemented_instruction(c); break;
	case 0x74: unimplemented_instruction(c); break;
	case 0x75: unimplemented_instruction(c); break;
	case 0x76: unimplemented_instruction(c); break;
	case 0x77: unimplemented_instruction(c); break;
	case 0x78: unimplemented_instruction(c); break;
	case 0x79: unimplemented_instruction(c); break;
	case 0x7a: unimplemented_instruction(c); break;
	case 0x7b: unimplemented_instruction(c); break;
	case 0x7c: unimplemented_instruction(c); break;
	case 0x7d: unimplemented_instruction(c); break;
	case 0x7e: unimplemented_instruction(c); break;
	case 0x7f: unimplemented_instruction(c); break;
		
	case 0x80:          // ADD B
		add(c, c->b, false);
		break;
	case 0x81:          // ADD C
		add(c, c->c, false);
		break;
	case 0x82:          // ADD D
		add(c, c->d, false);
		break;
	case 0x83:          // ADD C
		add(c, c->c, false);
		break;
	case 0x84:          // ADD H
		add(c, c->h, false);
		break;
	case 0x85:          // ADD L
		add(c, c->l, false);
		break;
	case 0x86:          // ADD M
		pair = (c->h << 8) | (c->l);
		add(c, c->read_memory(pair), 0);		
		break;
	case 0x87:          // ADD A
		add(c, c->a, 0);
		break;
	case 0x88:          // ADC B
		add(c, c->b, c->flags.cy);
		break;
	case 0x89:          // ADC C
		add(c, c->c, c->flags.cy);
		break;
	case 0x8a:          // ADC D
		add(c, c->d, c->flags.cy);
		break;
	case 0x8b:          // ADC E
		add(c, c->e, c->flags.cy);
		break;
	case 0x8c:          // ADC H
		add(c, c->h, c->flags.cy);
		break;
	case 0x8d:          // ADC L
		add(c, c->l, c->flags.cy);
		break;
	case 0x8e:          // ADC M
		pair = (c->h << 8) | (c->l);
		add(c, c->read_memory(pair), c->flags.cy);
		break;
	case 0x8f:          // ADC A
		add(c, c->a, c->flags.cy);
		break;
	case 0x90:          // SUB B
		sub(c, c->b, 0);
		break;
	case 0x91:          // SUB C
		sub(c, c->c, false);
		break;
	case 0x92:          // SUB D
		sub(c, c->d, false);
		break;
	case 0x93:          // SUB E
		sub(c, c->e, false);
		break;
	case 0x94:          // SUB H
		sub(c, c->h, false);
		break;
	case 0x95:          // SUB L
		sub(c, c->l, false);
		break;
	case 0x96:          // SUB M
		pair = (c->h << 8) | (c->l);
		sub(c, c->read_memory(pair), 0);
		break;
	case 0x97:          // SUB A
		sub(c, c->a, 0);
		break;
	case 0x98:          // SBB B
		sub(c, c->a, c->flags.cy);
		break;
	case 0x99:          // SBB C
		sub(c, c->c, c->flags.cy);
		break;
	case 0x9a:          // SBB D
		sub(c, c->d, c->flags.cy);
		break;
	case 0x9b:          // SBB E
		sub(c, c->e, c->flags.cy);
		break;
	case 0x9c:          // SBB H
		sub(c, c->h, c->flags.cy);
		break;
	case 0x9d:          // SBB L
		sub(c, c->l, c->flags.cy);
		break;
	case 0x9e:          // SBB M
		pair = (c->h << 8) | (c->l);
		sub(c, c->read_memory(pair), c->flags.cy);
		break;
	case 0x9f:          // SBB A
		sub(c, c->a, c->flags.cy);
		break;
	case 0xa0:          // ANA B
		unimplemented_instruction(c);
		break;
	case 0xa1: unimplemented_instruction(c); break;
	case 0xa2: unimplemented_instruction(c); break;
	case 0xa3: unimplemented_instruction(c); break;
	case 0xa4: unimplemented_instruction(c); break;
	case 0xa5: unimplemented_instruction(c); break;
	case 0xa6: unimplemented_instruction(c); break;
	case 0xa7: unimplemented_instruction(c); break;
	case 0xa8: unimplemented_instruction(c); break;
	case 0xa9: unimplemented_instruction(c); break;
	case 0xaa: unimplemented_instruction(c); break;
	case 0xab: unimplemented_instruction(c); break;
	case 0xac: unimplemented_instruction(c); break;
	case 0xad: unimplemented_instruction(c); break;
	case 0xae: unimplemented_instruction(c); break;
	case 0xaf: unimplemented_instruction(c); break;
	case 0xb0: unimplemented_instruction(c); break;
	case 0xb1: unimplemented_instruction(c); break;
	case 0xb2: unimplemented_instruction(c); break;
	case 0xb3: unimplemented_instruction(c); break;
	case 0xb4: unimplemented_instruction(c); break;
	case 0xb5: unimplemented_instruction(c); break;
	case 0xb6: unimplemented_instruction(c); break;
	case 0xb7: unimplemented_instruction(c); break;
	case 0xb8: unimplemented_instruction(c); break;
	case 0xb9: unimplemented_instruction(c); break;
	case 0xba: unimplemented_instruction(c); break;
	case 0xbb: unimplemented_instruction(c); break;
	case 0xbc: unimplemented_instruction(c); break;
	case 0xbd: unimplemented_instruction(c); break;
	case 0xbe: unimplemented_instruction(c); break;
	case 0xbf: unimplemented_instruction(c); break;
	case 0xc0: unimplemented_instruction(c); break;
	case 0xc1: unimplemented_instruction(c); break;
	case 0xc2: unimplemented_instruction(c); break;
	case 0xc3: unimplemented_instruction(c); break;
	case 0xc4: unimplemented_instruction(c); break;
	case 0xc5: unimplemented_instruction(c); break;
	case 0xc6:          // ADI D8
		add(c, c->read_memory(c->pc++), false);
		break;
	case 0xc7: unimplemented_instruction(c); break;
	case 0xc8: unimplemented_instruction(c); break;
	case 0xc9: unimplemented_instruction(c); break;
	case 0xca: unimplemented_instruction(c); break;
	case 0xcb: unimplemented_instruction(c); break;
	case 0xcc: unimplemented_instruction(c); break;
	case 0xcd: unimplemented_instruction(c); break;
	case 0xce:          // ACI D8
		t = c->read_memory(c->pc++);
		add(c, t, c->flags.cy);
		break;
	case 0xcf: unimplemented_instruction(c); break;
	case 0xd0: unimplemented_instruction(c); break;
	case 0xd1: unimplemented_instruction(c); break;
	case 0xd2: unimplemented_instruction(c); break;
	case 0xd3: unimplemented_instruction(c); break;
	case 0xd4: unimplemented_instruction(c); break;
	case 0xd5: unimplemented_instruction(c); break;
	case 0xd6: unimplemented_instruction(c); break;
	case 0xd7: unimplemented_instruction(c); break;
	case 0xd8: unimplemented_instruction(c); break;
	case 0xd9: unimplemented_instruction(c); break;
	case 0xda: unimplemented_instruction(c); break;
	case 0xdb: unimplemented_instruction(c); break;
	case 0xdc: unimplemented_instruction(c); break;
	case 0xdd: unimplemented_instruction(c); break;
	case 0xde: unimplemented_instruction(c); break;
	case 0xdf: unimplemented_instruction(c); break;
	case 0xe0: unimplemented_instruction(c); break;
	case 0xe1: unimplemented_instruction(c); break;
	case 0xe2: unimplemented_instruction(c); break;
	case 0xe3: unimplemented_instruction(c); break;
	case 0xe4: unimplemented_instruction(c); break;
	case 0xe5: unimplemented_instruction(c); break;
	case 0xe6: unimplemented_instruction(c); break;
	case 0xe7: unimplemented_instruction(c); break;
	case 0xe8: unimplemented_instruction(c); break;
	case 0xe9: unimplemented_instruction(c); break;
	case 0xea: unimplemented_instruction(c); break;
	case 0xeb: unimplemented_instruction(c); break;
	case 0xec: unimplemented_instruction(c); break;
	case 0xed: unimplemented_instruction(c); break;
	case 0xee: unimplemented_instruction(c); break;
	case 0xef: unimplemented_instruction(c); break;
	case 0xf0: unimplemented_instruction(c); break;
	case 0xf1: unimplemented_instruction(c); break;
	case 0xf2: unimplemented_instruction(c); break;
	case 0xf3: unimplemented_instruction(c); break;
	case 0xf4: unimplemented_instruction(c); break;
	case 0xf5: unimplemented_instruction(c); break;
	case 0xf6: unimplemented_instruction(c); break;
	case 0xf7: unimplemented_instruction(c); break;
	case 0xf8: unimplemented_instruction(c); break;
	case 0xf9: unimplemented_instruction(c); break;
	case 0xfa: unimplemented_instruction(c); break;
	case 0xfb: unimplemented_instruction(c); break;
	case 0xfc: unimplemented_instruction(c); break;
	case 0xfd: unimplemented_instruction(c); break;
	case 0xfe: unimplemented_instruction(c); break;
	case 0xff: unimplemented_instruction(c); break;
	}
}
