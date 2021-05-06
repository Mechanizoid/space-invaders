/* Intel 8080 cpu core */

#include <stdint.h>



/* CPU internal state: consits of accumulator, general purpose
 * registers, and the special register for condition flags
 */
struct Flags {
	uint8_t   z:   1;
	uint8_t   s:   1;
	uint8_t   p:   1;
	uint8_t   c:   1;
	uint8_t   ac:  1;
	uint8_t   pad: 1;
};


struct State {
	uint16_t pc;
	uint16_t sp;
	/* general purpose registers */
	uint8_t  a;
	uint8_t  b;
	uint8_t  c;
	uint8_t  d;
	uint8_t  e;
	uint8_t  h;
	uint8_t  l;
	/* special register for condition flags */
	struct Flags fr;
	
} cpu_state;

