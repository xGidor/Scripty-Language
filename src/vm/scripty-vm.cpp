#include <iostream>
#include <vector>
#include <stack>
#include "scripty-vm.hpp"
#include "logger.h"
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

ScriptyValue StackVM::eval()
{
    for(;;)
    {   
        auto opcode = READ_BYTE();
        switch (opcode)
        {
        case OP_HALT:
            return pop();
        case OP_CONST:
            push(GET_CONST());
            break;
        default:
            DIE << "Unknown opcode: " << std::hex << opcode;
        }
    }
}

ScriptyValue StackVM::exec(const std::string &program)
{   
    /*Parse the program & Compile program to Scripty Bytecode */
    
    constants.push_back(NUMBER(42));

    code = {OP_CONST, 0, OP_HALT};

    // Set instruction pointer.
    ip = &code[0];

    // Initialize the stackpointer
    sp = &stack[0];

    return eval();
}

int main()
{
    StackVM vm;
    auto result = vm.exec(R"(

        42

    )");

    log(AS_NUMBER(result));

    std::cout << "All Done!\n";

    return 0;
}