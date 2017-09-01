/* WEEK 3 NOTES - DATA REPRESENTATION (CONTINUED)
 *
 * Brian Lam
 */

// Pointers
Typically 32bit. Many types of pointers, one for each data type.
Pointer values [addresses] must be appropriate according to the data type.
(char *) ... can reference any byte address
(int *) ... must have addr%4 == 0
(double *) ... must have addr%8 == 0

// Floating point numbers
C has two floating point types:
float = 32 bit
double = 64 bit
// Printing floating point numbers
Print format for floating pointer numbers: '  printf("%W.Pf", (float)2.17828)  '
Where: 		W = total width of number, blank padded | P = #digits after point
printf("%10.4lf", (double)2.718281828459); OUTPUT:     2.7183 (4 whitespace pad in front)
printf("%20.20lf", (double)4.0/7);		   OUTPUT: 0.57142857142857139685

// IEEE 754 to floating point conversion
IEEE 754 is a standard for computing floating point numbers.
There are two types:
-> 32-bit single precision (bias = 127)
-> 64-bit double precision (bias = 1023)

Convert this single precision IEEE 754 nu into a floating point decimal value.
1 10000001 10110011001100110011010

'1' Separate the bits into three groups
-> Bit 31: leftmost bit, shows the SIGN +ve/-ve
-> Bit 23-30: next 8 bits, are the value of the EXPONENT
-> Bit 0-22: the remaining bits, give the FRACTION

'2' Check bit 31.
-> 1 = -ve | 0 = +ve

'3' Get the exponent and correct the bias.
-> A positive binary number: 10000001 = 129
-> Bias = 127, so 129 = 127 = 2.

'4' Convert fraction to decimal:
-> [   0   |    1     |     0    |    1     |    1  .. 001100110011001101]
-> (0*2^0) + (1*2^-1) + (0*2^-2) + (1*2^-3) + (1*2^-4)
->     0   +    1/2   +     0    +    1/8   +    1/16

'5' Multiple the three components together
-> SIGN (+ve or -ve) = -1
-> FRACTION (1 + decimal) = 1.7000000476837158
-> EXPONENT (2 ^ value - bias) = 2^129-127 = 2^2
-> SIGN * FRACTION * EXP = (-1) * (1.7000000476837158) * 4 =~ -6.8

// Arrays
&v[0] = Address of first element
*(v+i) = Array indexing v[i]
Strings are just arrays of char with a '\0' terminator
- Constant strings have '\0' added automatically
- String buffers must allow for a space to hold '\0' i.e. char str[5] = "abc"
Initialising strings:
- char a[9] = " a string";  | char *b = "a string";
- char c[9] = {'a', ' ', 's', 't', 'r' , 'i', 'n', 'g', '\0'}; | - char *d = {'a', ' ', 's', 't', 'r' , 'i', 'n', 'g', '\0'};

// Structs and Struct Offsets
Structs are made up of components: Each component has a NAME and TYPE
Each name maps to a byte offset within the struct.
E.g. Name 'a' Type 'char' has offset = 0 in the struct s1.
struct _s1 {
   char   a[6];  // array of 6 1-byte chars		OFFSET = 0
   int    b;     // 4-byte int
   char   c;     // 1-byte char
   double d;     // 8-byte int
   int    e;     // 4-byte int
   char   f;     // 1-byte char
};

If you have a struct with many different types, you should declare the types
in an appropriate order so that you dont waste space with padding.				  STRUCT
E.g. dont start with a char then an int, otherwise you waste 3 bytes for padding. | char | pad | pad | pad |
	(Structs start on a 4-byte boundary. ints are laid out on a 4-byte boundary)  |  int | int | int | int |

// Variable length structs
Amount of memory allocated to a struct is determined dynamically.


// Bit-wise structs
Bit-field structs:
- Specify unnamed COMPONENTS using standard types
- Specify named individual BIT-FIELDS in each component

struct _bit_fields {
	unsigned int first_bit	  : 1,			' unsigned int = component '
				 next_7_bits  : 7,			' first_bit etc. = bit-fields '
				 last_24_bits : 24;
}
sizeof(struct _bit_fields) is 4 bytes -> 24 + 7 + 1 = 32 bits = 4 bytes

Another example:

/* GRAPHICS OBJECTS */
struct _object { // comprised of two 32-bit words
	unsigned int 	red		: 5,	// 5 bits for red
					blue	: 5,	// 5 bits for blue
					green	: 5,	// 5 bits for green
					pad 	: 1,	// 1 bit to pad to short
					ident	: 16;	// 16 bits for object ID
	unsigned int 	height  : 6,	// 6 bits for object height
					width 	: 6,	// 6 bits for object width
					xcoord 	: 9,	// 9 bits for x-coordinate
					ycoord	: 9;	// 9 bits for y-coordinate
}

struct _object oval;
.
.
oval.red = 4; oval.blue = 31; oval.green = 15;
oval.height = 5; oval.width = 15;
/* END OF EXAMPLE */

Bit-fields provide an alternative to bit operators and masks:

typedef unsigned int uint;         struct _privs {
typedef uint privs;                   unsigned int
#define OWNER_READ  (1 << 8)             owner_read  : 1,
#define OWNER_WRITE (1 << 7)             owner_write : 1,
#define OWNER_EXEC  (1 << 6)             owner_exec  : 1,
...                                      ...
#define OTHER_WRITE (1 << 1)             other_write : 1,
#define OTHER_EXEC  (1 << 0)             other_exec  : 1;
unsigned int myPrivs;              } myPrivs;

// give owner execute permission on file
myPrivs |= OWNER_EXEC;             myPrivs.owner_exec = 1;

// prevent others from writing on file
myPrivs &= ~OTHER_WRITE;           myPrivs.other_write = 0;

// check whether file is readable to all
open = myPrivs & OTHER_READ;       open = myPrivs.other_read;





















