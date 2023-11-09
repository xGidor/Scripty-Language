#include <iostream>
#include <vector>
#include <stack>
#include <cctype> 

#include "scripty-vm.hpp"
#include "logger.hpp"
#include "values.h"
#include "types.h"

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
            DIE << "NOT_IMPLEMENTED()\n";
            // Need to implement local variable storing.
            break;
        
        case ILOAD : case FLOAD : case SLOAD : case LLOAD : case ALOAD : case ZLOAD : // type variable loading (basically copying to the top of the stack)
            DIE << "NOT_IMPLEMENTED()\n";
            //push(LOAD_CONST()); // need to implement local variables
            break;

        case ICONST : case FCONST : case SCONST : case LCONST : case ACONST : case ZCONST : // type constants
            push(GET_CONST());
            break;

        /* Call a function object */
        case CALLFUNC:
            DIE << "NOT_IMPLEMENTED()\n";
            break;

        /* Create a class object */
        case MCLASS: {
            ScriptyValue stackValue = pop();
            ScriptyClass* newClass;
            if (stackValue.type != ScriptyValueType::STRING)
            {
                DIE << "MCLASS(): Value mismatch!\n";
            }
            newClass->name = stackValue.text;

            classes.push_back(*newClass);

            break;
        }
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

        /* Make a function object */
        case MFUNC: {
        //    int parameters = READ_BYTE(); // Read how many parameters do wee need.
        //    std::vector<ScriptyParameter> paramVector(parameters); // so if we have 2 parameters it should pass in 1 right?
//
        //    READ_BYTE();
        //    std::string functionName = pop().text;
        //    
        //    for (size_t i = 0; i < parameters; i++)
        //    {
        //        auto currCode = READ_BYTE();
        //        if (currCode == ICONST)
        //        {
        //            auto nextCode = READ_BYTE();
        //            if (nextCode != INULL)
        //            {
        //            
        //            }
        //            
        //        }
        //        ScriptyValue stackVarValue = pop();
        //        ScriptyValue stackVarName = pop();
        //        ScriptyParameter* param;
        //        param->name = stackVarName.text;
        //       // param->type
//
        //       paramVector[i] = *param;
        //    }
        //    
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
    
    //constants.push_back(FLOAT(10.0f));
    //constants.push_back(INTEGER(3));
    //constants.push_back(INTEGER(10));
    constants.push_back(STRING("Main"));
    constants.push_back(STRING("a")); // varname a
    constants.push_back(INTEGER(2)); // default parameter for b
    constants.push_back(STRING("b")); // varname b

    code = {
        MFUNC, 2, // 2 means 2 parameters
        SCONST, 0, // Function name "Main".

        ICONST, INULL,// Value for first parameter variable, pushing empty constant defaults to null
        SCONST, 1, // Get the name for the first parameter "a"

        ICONST, 2, // Value for second parameter
        SCONST, 3, // Get the name for the second parameter "b"

        HALT
    };

    //code = {ICONST, 2, FCONST, 0, ICONST, 1, FMUL, ILOAD, 2, FSUB, HALT};

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
