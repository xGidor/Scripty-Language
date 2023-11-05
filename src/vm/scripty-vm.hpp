#ifndef __ScriptyVM_h
#define __ScriptyVM_h

#include <iostream>
#include <vector>
#include <array>

#include "bytecode/OpCode.h"
#include "values.h"

/**
 * Reads the next byte in the bytecode and advances the Instruction Pointer
*/
#define READ_BYTE() *ip++

/**
 * Get Constant from the pool
*/
#define GET_CONST() constants[READ_BYTE()]

/**
 * Binary Operations
*/
#define BINARY_OP(op)            \
  do                             \
  {                              \
    auto op2 = AS_NUMBER(pop()); \
    auto op1 = AS_NUMBER(pop()); \
    push(NUMBER(op1 op op2));    \
  } while (false);
  


/**
 * Stack Top (Overflow after exceeding)
*/
#define STACK_LIMIT 512

class StackVM {
  public:
    StackVM() {}

    /* Stack Operations */
    void push(const ScriptyValue& value);
    ScriptyValue pop();

    /* Executes the program */
    ScriptyValue exec(const std::string &program);

    /* Main Eval Loop */
    ScriptyValue eval();

    /* Instruction Pointer (Program Counter) */
    uint8_t* ip;

    /* Stack Pointer */
    ScriptyValue* sp;

    /* Stack Operands */
    std::array<ScriptyValue, STACK_LIMIT> stack;

    /* Constant Pool */
    std::vector<ScriptyValue> constants;

    /* Bytecode */
    std::vector<uint8_t> code;

};

#endif