
#ifndef	BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO)) // For example !

#define CLR_BIT(REG,Bit_NO)	 (REG) &= ~(1<<(Bit_NO))

// Get The Bit number Bit_NO
#define GET_BIT(REG,Bit_NO)	REG=((REG & (1<<Bit_NO))>>Bit_NO)

// Right Shift by No
#define RSHFT_REG(REG,NO)	(REG)>>=(NO)

// Left Shift by NO
#define LSHFT_REG(REG,NO)	(REG)<<=(NO)


// Circular Left Shift
#define CLSHFT_REG(REG,NO)	(REG)=(REG<<NO)^(REG-NO)

// Assign a Value to a Register
#define ASSIGN_REG(REG,VALUE) (REG)=(VALUE)

// Set The Register [1s]
#define SET_REG(REG)        (REG)|=(0xFFFF)

// Clear the Register [0s]
#define CLR_REG(REG)	(REG)&=(0)

// Toggle a Bit in Register
#define TGL_BIT(REG,Bit_NO)	(REG) ^= (1<<(Bit_NO))

// Toggle a Register Value
#define TGL_REG(REG)			(REG)=~(REG)

// Set The High Nibble in a Register
#define SET_H_NIB(REG)			(REG)|=(0x0F0)

// Set The Low Nibble in a Register
#define SET_L_NIB(REG)		(REG)|=(0x00F)

// Clear The High Nibble in a Register
#define CLR_H_NIB(REG)			(REG)&=~(0x0F0)

// Clear The Low Nibble in a Register
#define CLR_L_NIB(REG)	(REG)&=~(0x00F)

// Get The High Nibble in a Register
#define GET_H_NIB(REG)(REG)=((REG&0X0F0)>>4)

// Get The Low Nibble in a Register
#define GET_L_NIB(REG) (REG)=(REG&0X0F)

// Assign The High Nibble in a Register
#define ASSIGN_H_NIB(REG,VALUE)   (REG)=(VALUE<<4)|(REG&0XFF0F)

// Assign the Low Nibble in a Register
#define ASSIGN_L_NIB(REG,VALUE)(REG)=(VALUE)|(REG&0XF0)

// Toggle the High Nibble in a Register
#define TGL_H_NIB(REG)(REG) ^= (0x00F0)

// Toggle the Low Nibble in a Register
#define TGL_L_NIB(REG)			(REG) ^= (0x000F)

// Swap the Nibbles in a Register
#define SWAP_NIB(REG)	(REG)=(REG<<4)|(REG>>4)

#endif/*BIT_MATH_H*/