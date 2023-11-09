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
 * Inspect top value without popping it.
*/
ScriptyValue StackVM::peek() 
{
    if (sp == stack.begin()) {
        DIE << "peek(): Empty Stack!\n";
    }
    
    return *(sp - 1);  // Access the value at the top of the stack without popping it.
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
        case HALT:
            return pop();
            
        case ISTORE : case FSTORE : case SSTORE : case LSTORE : case ASTORE : case ZSTORE :
            // Need to implement local variable storing.
            break;
        
        case ILOAD : case FLOAD : case SLOAD : case LLOAD : case ALOAD : case ZLOAD : // type variable loading (basically copying to the top of the stack)
            //push(LOAD_CONST()); // need to implement local variables
            break;

        case ICONST : case FCONST : case SCONST : case LCONST : case ACONST : case ZCONST : // type constants
            push(GET_CONST());
            break;

        case CALLFUNC:
            break;

        case MCLASS:
            auto nameValue = pop();

            // Implement fields and method creation
            
            ScriptyClass* makeClass;
            if(nameValue.type != ScriptyValueType::STRING)
            {    
                DIE << "MakeClass(): Encountered invalid value type for name.\n";
            }
            makeClass->name = nameValue.text;

            classes.push_back(*makeClass);
            break;

        case MFUNC:
            break;
            
        // Math operations
        case IADD: {// Addition instructions for INT
            INTOP(+);
            break;
        }

        case ISUB: {// Subtract instructions for INT
            INTOP(-);
            break;
        }

        case IMUL: {// Multiply instructions for INT
            INTOP(*);
            break;
        }

        case IDIV: {// Division instructions for INT
            INTOP(/);
            break;
        }
        case FADD: {// Addition instructions for FLOAT
            FLOATOP(+);
            break;
        }

        case FSUB: {// Subtract instructions for FLOAT
            FLOATOP(-);
            break;
        }

        case FMUL: {// Multiply instructions for FLOAT
            FLOATOP(*);
            break;
        }

        case FDIV: {// Division instructions for FLOAT
            FLOATOP(/);
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
    
    constants.push_back(FLOAT(10.0f));
    constants.push_back(INTEGER(3));
    constants.push_back(INTEGER(10));
    
    code = {ICONST, 2, FCONST, 0, ICONST, 1, FMUL, ILOAD, 2, FSUB, HALT};

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
