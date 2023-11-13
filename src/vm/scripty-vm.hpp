#ifndef __ScriptyVM_h
#define __ScriptyVM_h

#include <iostream>
#include <vector>
#include <array>
#include <cmath>


#include "bytecode/OpCode.h"
#include "values.h"
#include "types.h"

/**
 * Reads the next byte in the bytecode and advances the Instruction Pointer
*/
#define READ_BYTE() *ip++
#define UNREAD_BYTE() *ip--

/**
 * Get Constant from the pool
*/
#define GET_CONST() constants[READ_BYTE()]

/**
 * Load Constant from the pool (same as get_const for now)
*/
#define LOAD_CONST() constants[READ_BYTE()]


/**
 * Binary Operations
*/
#define INTOP(op)                               \
  do                                            \
  {                                             \
    auto op2 = AS_INT(pop());                   \
    auto op1 = AS_INT(pop());                   \
    int result = op1 op op2;                    \
    push(INTEGER_(result));                      \
  } while (false);
  

#define FLOATOP(op)                             \
  do                                            \
  {                                             \
    auto op2 = AS_FLOAT(pop());                 \
    auto op1 = AS_FLOAT(pop());                 \
    float result = op1 op op2;                  \
    push(FLOAT_(result));                        \
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
    
    ScriptyValue peek();

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

    /* Program Methods */
    std::vector<ScriptyFunction> functions;

    /* Program Classes */
    std::vector<ScriptyClass> classes;

    /* Constant Pool */
    std::vector<ScriptyValue> constants;

    /* Bytecode */
    std::vector<uint8_t> code;

};

#endif