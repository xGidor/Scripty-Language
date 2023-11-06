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


/**
 * Return and break statements
*/
#define RETURN_VALUE 0x01
#define BREAK_LOOP 0x02

/**
 * Class and functions
*/
#define MAKE_FUNCTION 0x03
#define CALL_FUNCTION 0x04
#define BUILD_CLASS 0x05
#define STORE_NAME 0x06

/**
 * For Loops
*/
#define FOR_LOOP 0x07

/**
 * stops the program
*/
#define HALT 0xff


#endif
