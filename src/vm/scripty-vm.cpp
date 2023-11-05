#include <iostream>
#include <vector>
#include <stack>
#include "scripty-vm.hpp"
#include "logger.hpp"
#include "values.h"

/*
*Push values onto the stack
*/
void StackVM::push(const ScriptyValue& value)
{
    if (sp == stack.end())
    {
        DIE << "push(): Stack Overflow!\n";
    }
    
    *sp = value;
    sp++;
}

/**
 * Pop values from the stack
*/
ScriptyValue StackVM::pop()
{   
    if (sp == stack.begin())
    {
        DIE << "pop(): Empty Stack!\n";
    }
    
    --sp;
    return *sp;
}

/**
 * Evaluate the current bytecode.
*/
ScriptyValue StackVM::eval()
{
    for(;;)
    {   
        auto opcode = READ_BYTE();
        switch (opcode)
        {
        case OP_HALT:
            return pop();
        case OP_CONST: // constants
            push(GET_CONST());
            break;

        // Math operations
        case OP_ADD: {// Addition instructions
            BINARY_OP(+);
            break;
        }

        case OP_SUB: {// Subtract instructions
            BINARY_OP(-);
            break;
        }

        case OP_MUL: {// Multiply instructions
            BINARY_OP(*);
            break;
        }

        case OP_DIV: {// Division instructions
            BINARY_OP(/);
            break;
        }
        default:
            DIE << "Unknown opcode: " << std::hex << opcode;
        }
    }
}

/**
 * Execute the current string/program (Not Implemented Yet)
*/
ScriptyValue StackVM::exec(const std::string &program)
{   
    /*Parse the program & Compile program to Scripty Bytecode */
    
    constants.push_back(FLOAT(10));
    constants.push_back(INTEGER(3));
    constants.push_back(INTEGER(10));
    
    code = {OP_CONST, 0, OP_CONST, 1, OP_MUL, OP_CONST, 2, OP_SUB, OP_HALT};

    // Set instruction pointer.
    ip = &code[0];

    // Initialize the stackpointer
    sp = &stack[0];

    return eval();
}


/**
 * Main VM Execution
*/
int main()
{
    StackVM vm;
    auto result = vm.exec(R"(

        asd

    )");

    log(AS_FLOAT(result));

    std::cout << "All Done!\n";

    return 0;
}