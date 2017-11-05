/* WEEK 1 NOTES - INTRODUCTION
 *
 * Brian Lam
 */

// C is a step up from assembly language.
Stack: Last In First Out
- push(), pop(), top, size
- used in implementation of functions compiled in C

Queue: First In First Out
- enqueue() dequeue(), head, tail, size
- used in scheduling, managing resource usage

// Bits
// The below are common sizes and don't apply to all hardware
char = 1 byte = 8 bits 	 	'a' is 0110 0001
short = 2 bytes = 16 bits 	 42 is 0000 0000 0010 1010
int = 4 bytes = 32 bits 	 42 is 0000 .... 0010 1010
double = 8 bytes = 64 bits

// C Bitwise Operators
Bitwise Operations: '& | ^ ~ << >>'

Checking status of a bit:
- Use bitwise ' & ' / Set mask bit = 1
- Using bitwise ' & ' with a mask = 1 will return unchanged bit input

Setting bits ON:
- Use bitwise ' | ' / Set mask bit = 1

Setting bits OFF:
- Use bitwise ' & ' / Set mask bit = 0

Toggling bits ON or OFF:
- Sometimes we may need to change values to BOTH on and off
- We can juse bitwise XOR ' ^ ' to invert the bit value to toggle it

Negation of bits:
- You can negate whole sequence of bits using ' ~ '
- No use of a mask, simply ' ~ ( bit sequence ) '

Shifting bits LEFT:
- Shift a sequence of bits LEFT, by X positions ' << X '
- LHS bits are removed / truncated, RHS bits are replaced by 0

Shifting bits RIGHT:
- Shift a sequence of bits RIGHT, by X positions ' >> X '
- LHS bits are replaced by 0, RHS bits are removed / truncated
- If the value is SIGNED, the SIGNED-BITS replaces the LHS

