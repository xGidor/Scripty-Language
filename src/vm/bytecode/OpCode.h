/**
 * Instruction set for Scripty VM
*/

#ifndef OpCode_h
#define OpCode_h

/**
 * Const and variable codes
 * Ints
*/
#define ICONST 0x0a // push int constant
#define ISTORE 0x0b // store int into local variable
#define ILOAD 0x0c // load int from local variable

/**
 * Floats
*/
#define FCONST 0x1a // push float constant
#define FSTORE 0x1b // store float into local variable
#define FLOAD 0x1c // load float from local variable

/**
 * Objects
*/
#define ACONST 0x2a // push object constant
#define ASTORE 0x2b // store object into local variable
#define ALOAD 0x2c // load oject from local variable

/**
 * Bools
*/
#define ZCONST 0x3a // push bool constant
#define ZSTORE 0x3b // store bool into local variable
#define ZLOAD 0x3c // load bool from local variable

/**
 * Strings
*/
#define SCONST 0x4a // push string constant
#define SSTORE 0x4b // store string into local variable
#define SLOAD 0x4c // load string from local variable

/**
 * Lists
*/
#define LCONST 0x5a // push list constant
#define LSTORE 0x5b // store list into local variable
#define LLOAD 0x5c // load list from local variable


/**
 * Math instructions (Operations)
*/
#define IADD 0x0d
#define ISUB 0x1d
#define IMUL 0x2d
#define IDIV 0x3d
#define FADD 0x4d
#define FSUB 0x5d
#define FMUL 0x6d
#define FDIV 0x7d
#define SADD 0x8d
#define SSUB 0x9d
#define SMUL 0xd1
#define SDIV 0xd2
#define LADD 0xd3
#define LSUB 0xd4
#define LMUL 0xd5
#define LDIV 0xd6

/**
 * Return and break statements
*/
#define RETURN 0x01 // Used for returning.
#define BREAK 0x02 // Used for breaking a loop

/**
 * Class and functions
*/
#define MFUNC 0x03 // Used for making a function
#define CALLFUNC 0x04 // Used for calling a function
#define MCLASS 0x05 // Used for making a class
#define STORE_NAME 0x06

/**
 * For Loops
*/
#define FORLOOP 0x07

/**
 * stops the program
*/
#define HALT 0xff


#endif
