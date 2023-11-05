#ifndef __ScriptyVM_h
#define __ScriptyVM_h

#include <iostream>
#include <vector>
#include <array>

#include "OpCode.h"
#include "values.h"

/**
 * Reads the next byte in the bytecode and advances the Instruction Pointer
*/
#define READ_BYTE() *ip++

/**
 * Stack Top (Overflow after exceeding)
*/
#define STACK_LIMIT 512

class StackVM {
  public:
    StackVM() {}

    void push(ScriptyValue value);

    /* Executes the program */
    void exec(const std::string &program);

    /*Main Eval Loop*/
    void eval();

    /* Instruction Pointer (Program Counter) */
    uint8_t* ip;

    /* Stack Pointer */
    uint8_t* sp;

    /* Stack Operands */
    std::array<ScriptyValue, STACK_LIMIT> stack;


    /* Constant Pool */
    std::vector<ScriptyValue> constants;

    /* Bytecode */
    std::vector<uint8_t> code;

};

#endif