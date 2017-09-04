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
	.space i*j	// 2d array
v7:
	.space 8    // struct (2 ints * 4 bytes each)
v8:
	.
v9:
	.space      // array of pointers to the struct object
				// 16 bytes = 4 pointers * 4 bytes each

// ^^^You can create a C program to test the above

Q3. Consider the following MIPS data structure representing the Danish Flag
See code in notes

Q5. For each
(a) how does it arrange itself in memory
- Size = 16 bytes (2 doubles * 8 bytes each)
- X offset = 0
- Y offset = 8
(b)
- Size = 8 bytes (1 int + 1 pointer)
- value offset = 0
- next offset = 4
(c)
- Size = int + char[9] + char[5] + char[3] + double = 4 + 9 + 5 + 3 + 8 = 29 + 3 final_pad = 32 bytes
- stu_id offset = 0
- char[9] offset = 4
- char[5] offset = 

^ objects in the struct are both byte aligned, therefore we can fit the next object into the struct
  left by the previous one. We only need to pad in the final word object (fina_byte).

  padding only needs to be there when we need to do word alignment.
  E.g. the double needs to be padded in the final word as the double needs to be a multiple of 4

  		   bytes
  1  2  3  4  5  6  7  8
 [    int   ][  course			row 1
    course  ][   term			  .
    ][ grade][    pad   ]   	  .
 [       double: mark   ]		row 4


(d)
- Size = int int int int Item = 5 x 4 = 20 bytes
- Offset is easy

/*
 * Prologue / Epilogue
 */

PROLOGUE: Push all to the stack
EPILOGUE: Grab everything and reset the way we found it



/*
 *	ASSIGNMENT STUFF
 */
arrays cant be local, they must be declared at the top.
In MIPS, everything we declare must be at the very top of the '.data segment'