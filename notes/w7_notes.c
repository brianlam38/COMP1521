// WEEK 7 NOTES

/*
 * C Pre-Processor
 */
How does the compiler convert C -> MIPS?
-> Converts #include #define
-> Parse code to make sure syntax is correct
-> Manage a list of symbols used in the program
-> Decide how to rep data structures
-> Alloc local vars to registers / stack
-> Map control structurs to MIPS instructions

Example substitutions:
'#include file.h' = replaces #include by contents of file.h
'#define Name Const' = replaces all occurrences of symbol Name by Constant value
'#define Name(Params) Expression' = replace Name(Params) by Expression

Pre-Processor commands get evaluated before actual compilation.
Code inside pre-processor block doesnt appear when compiled:
	#include Inserts a header from another file
	#define  Substitutes a macro
	#if 	 Tests if a condition is true
	#else	 The alternative for #if
	#elif	 #else and #if
	#endif	 Ends pre-processor conditional
	#error	 Prints error message on stderr
	#ifdef	 Ret true if this macro is defined
	#ifndef	 Ret true if this macro is NOT defined
Usage: Debugging
	// if DEBUG macro is defined (by passing -DDEBUG flag to gcc compiler), then run debugging tests
	#ifdef DEBUG
   		/* Your debugging statements here */
	#endif

// Compiler: Symbol Table Management
Compiler keeps track of names, resolves symbols to specific locations - data/stack/registers

// Local Variables
Two choices for storing local vars:
1. In stack = persist for whole function, but lw/sw needed in MIPS
2. In register = efficient, not many registers but is useful if var is used in small scope

// Expression evaluation
Uses temporary registers:
-> Even complex expressions dont generally need > 3-4 registers









	