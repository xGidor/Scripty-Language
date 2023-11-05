#include <iostream>
#include <vector>
#include <stack>
#include "scripty-vm.hpp"
#include "logger.h"
#include "values.h"

void StackVM::eval()
{
    for(;;)
    {   
        auto opcode = READ_BYTE();
        log(opcode);
        switch (opcode)
        {
        case OP_HALT:
            return;
        case OP_CONST:
            auto constIndex = READ_BYTE();
            auto constant = constants[constIndex];
            push(constant);
            break;
        default:
            DIE << "Unknown opcode: " << std::hex << opcode;
        }
    }
}

void StackVM::exec(const std::string &program)
{   
    /*Parse the program & Compile program to Scripty Bytecode */
    
    constants.push_back(NUMBER(42));

    code = {OP_CONST, 0, OP_HALT};

    // Set instruction pointer.
    ip = &code[0];

    return eval();
}

int main(int argc, char const *argv)
{
    StackVM vm;
    vm.exec(R"(

        42

    )");

    std::cout << "All Done!\n";

    return 0;
}