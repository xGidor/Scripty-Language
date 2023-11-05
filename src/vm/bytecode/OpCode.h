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
 * stops the program
*/
#define OP_HALT 0xff


#endif