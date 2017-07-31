// Interface to ADT for Bits bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017

#ifndef QUEUE_H
#define QUEUE_H

typedef struct BitsRep *Bits;

// make a new zero'd Bits with N bits
Bits makeBits(int N);
// release space used by Bits
void  freeBits(Bits b);
// bit-wise AND of two Bits a, b
void andBits(Bits a, Bits b, Bits res);
// bit-wise OR of two Bits a, b
void orBits(Bits a, Bits b, Bits res);
// bit-wise negation of Bits a
void invertBits(Bits a, Bits res);
// left shift by N bit positions
void leftShiftBits(Bits b, int N, Bits res);
// right shift by N bit positions
void rightShiftBits(Bits b, int N, Bits res);
// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to);
// set Bits from a string of 0's and 1's
void setBitsFromString(Bits b, char *str);
// display Bits as sequence of 0's and 1's
void showBits(Bits b);

#endif
