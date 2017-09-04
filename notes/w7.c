/*
 *	Week 7 Tutorial Notes
 */

Biggest thing in assignment:
- Clean, neat, understandable code + correctness
- Comments etc.

Q1. Give MIPS directives to represent the following vars:

v0:				
	.space 4	// int v0;
v1:
	.word 42	// int v1 = 42;
v2:
	.space 1	// char v2;
v3:
	.word					// char v3 = 'a';
	.asciiz "hello ..."
	.byte 'a'
v4:
	.
v5:
	.space 80	// 80 = 4 (sizeof byte) * 20 inices
v6:
	.			// 2d array

/*
 *	ASSIGNMENT STUFF
 */
arrays cant be local, they must be declared at the top.
In MIPS, everything we declare must be at the very top of the '.data segment'