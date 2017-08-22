/* WEEK 2 NOTES - MEMORY AND DATA
 *
 * Brian Lam
 */

// Memory and Data
Memory goes DOWNWARDS from HIGHEST to LOWEST memory addresses: 0xFFFFFFFF -> 0x00000000
Memory = an array of bytes, where each index is a pointer

// Data bytes in REGISTERS may be in different order to MEMORY
// Big / Little Endian describe the order in which a sequence of bytes are stored in memory.
BIG ENDIAN:
- The "big end" = most significant values are stored first
- '| byte3 | byte2 | byte1 | byte0 |' MSB -> LSB

LITTLE ENDIAN:
- The "litte end" = least significant values are stored first
- '| byte0 | byte1 | byte2 | byte3 |' LSB -> MSB

Memory allows you to:
- Load bit-strings of sizes 1,2,4,8 bytes from N-byte boundary addresses into registers in the CPU

You are presented with a string of 8, 16, 32, 64 bits
Need to interpret this bit-string as a meaningful value
Data representations provide a way of assigning meaning to bit-strings

// Character Data
Character data has several representations / encodings
Two most common are:
(1) ASCII
- 7bit values, using lower 7-bits of a byte. Top bit / 8th bit is always 0.
- Can encode roman alphabet, digits, punctuation, control chars '\0 \n' etc.
- Refer to an ASCII table for ASCII character encoding
(2) UTF-8 (Unicode)
- 8bit values, with ability to extend to multi-byte values
- Can encode all human languages plus other symbols such as emojis / math symbols etc.

// UTF-8 Encoding
UTF-8 uses variable-length encoding.

#bytes |  #bits |  Byte 1  |  Byte 2  |  Byte 3  |  Byte 4	 |	127 1-byte codes are compatible with ASCII
	1  |	7	| 0xxxxxxx |	-	  |		-	 |	  -		 |	2047 2-byte codes include most Latin alphabets
	2  |	11	| 110xxxxx | 10xxxxxx |		-	 |	  -		 |	65536 3-byte codes include most Asian languages
	3  |	16	| 1110xxxx | 10xxxxxx |	10xxxxxx |	  -		 |	2097152 4-byte codes include symbols/emojis etc.
	4  |	21	| 11110xxx | 10xxxxxx |	10xxxxxx |	10xxxxxx |

The following two notations work in some contexts:
- \uHexDigits ... insert Unicode values 		"abc\xE2\x86\xABdef"
- \x2HexDigits ... insert individual bytes		u"abc\u21ABdef"

// Integer constants
There are three ways to write integer constants in C:
(1) 'signed decimal' (0..9) = 42
(2) 'unsigned hex'	 (0..F) = 0x2A    [ 42 in dec ]
(3) 'signed octal'	 (0..7) = 052     [ 42 in dec ]
Three variations:
(1) 'unsigned int' (32 bits / 4 bytes) = 123U	unsigned range = [ 0..2^32 -1 ]
(2) 'long int'	   (64 bits / 8 bytes) = 123L 
(3) 'short int'	   (16 bits / 2 bytes) = 123S

// Signed integers
signed range = [ 0..2^31 -1 ]
Several ways of representing negative values:
[ example below = -5 / unsigned 0000 0101]
(1) 'signed magnitude' ... 1000 0101 = first bit is the sign, rest are magnitude
(2) 'ones complement'  ... 1111 1010 = form -N by inverting all bits in N
(3)	'twos complement'  ... 1111 1011 = form -N by inverting all bits in N and adding 1
In all representations, +ve numbers have 0 in leftmost bit

'signed magnitude' Easy to form -ve X from X = OR | in high-order bit
'ones complement'  Easy to form -ve X from X = NEG ~ all bits
'twos complement'  Form -ve X from X 		 = NEG ~ all bits + 1

Twos Complement is the most efficient way to represent signed integers. Most computers use this.
- Only has ONE VALUE for 0
--> [ 0000 0000 ]
- Ones Complement & Signed Magnitude has TWO VALUES -ve 0 and +ve 0 
--> +ve zero: [ +0 = 0000 0000 ]
--> -ve zero: [ -0 = 1111 1111 + 1 = 0000 0000 ]



