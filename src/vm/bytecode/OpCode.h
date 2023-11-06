/**
 * Instruction set for Scripty VM
*/

#ifndef OpCode_h
#define OpCode_h

/**
 * Pushes a const onto the stack
*/
#define OP_CONST 0x00

/**
 * Math instructions 
*/
#define OP_ADD 0x01
#define OP_SUB 0x02
#define OP_MUL 0x03
#define OP_DIV 0x04

/**
 * Return and break statements
*/
#define OP_RETURN_VALUE 0x05
#define OP_BREAK_LOOP 0x06

/**
 * Class and functions
*/
#define OP_BUILD_CLASS 0x07
#define OP_MAKE_FUNCTION 0x08
#define OP_CALL_FUNCTION 0x09
#define OP_BUILD_CLASS 0x10

/**
 * For Loops
*/
#define OP_FOR_LOOP 0x11

/**
 * stops the program
*/
#define OP_HALT 0xff


#endif
