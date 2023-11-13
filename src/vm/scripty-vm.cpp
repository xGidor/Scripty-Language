#include <iostream>
#include <vector>
#include <stack>
#include <cctype> 

#include "scripty-vm.hpp"
#include "logger.hpp"
//#include "values.h"

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
            ScriptyClass newClass;
            if (stackValue.type != ScriptyValueType::STRING)
                DIE << "MakeClass(): Value mismatch!\n";

            newClass.name = stackValue.text;

            classes.push_back(newClass);

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

        /* Puts a method into a classes function list */
        case PUTFUNC: {
            if (classes.size() == 0)
                DIE << "PutFunc(): No class were declared.\n";

            if (functions.size() == 0)
                DIE << "PutFunc(): No method were declared.\n";
            
            classes.back().methods.push_back(functions.back()); // add the function to the class scope
            functions.pop_back(); // remove the function from the global scope.
            break;
        }
            
        /* Puts a constant/variable into a classes field list */
        case PUTFIELD: {
            if (classes.size() == 0)
                DIE << "PutField(): No class were declared.\n";
            
            ScriptyValue stackValue = pop();
            ScriptyVariable newField;
            ScriptyValue stackStrValue = pop();
            if (stackStrValue.type != ScriptyValueType::STRING)
                DIE << "PutField(): Value mismatch!\n";
            
            newField.name = stackStrValue.text;
            newField.type = stackValue.type;
            newField.value = stackValue;
            classes.back().fields.push_back(newField);
            break;
        }

        /* Make a function object */
        case MFUNC: {
            int parameters = READ_BYTE(); // Read how many parameters do we need.
            std::vector<ScriptyParameter> paramVector(parameters); // Create a temporary Vector to store the parameters int.

            ScriptyValue stackValue = pop(); // Pop our name Value from the top of the stack.
            if (stackValue.type != ScriptyValueType::STRING)
                DIE << "MakeFunc(): Value mismatch!\n";

            ScriptyFunction newMethod; // Create the new function base.
            newMethod.name = stackValue.text;  // Set the function name.

            for (size_t i = 0; i < parameters; i++)
            {   
                ScriptyParameter param; // Create a new parameter instance
                ScriptyValue stackNameVal = pop(); // pop the top value from the stack which is expected to be a string, aka the name of the parameter
                if (stackNameVal.type != ScriptyValueType::STRING)
                    DIE << "MakeFunc().MakeParams(): Value mismatch!\n";
                
                ScriptyValue stackValueVal = pop(); // pop the top value from the stack which could be any value.
                param.name = stackNameVal.text; // Set the parameter name
                param.type = stackValueVal.type; // Set the parameter type
                if (stackValueVal.type != param.type)
                    DIE << "MakeFunc().MakeParams(): Value mismatch!\n";
                
                param.defaultValue = stackValueVal; // Set the default value to the popped value constant

                paramVector.push_back(param); // Push the parameter to the paramVector list.
            }

            newMethod.parameters = paramVector; // set the new vector to newMethod() parameters vector

            switch (READ_BYTE()) // Read the next byte which should specify the return type of the function.
            {
            case IRETURN:
                newMethod.returnType = ScriptyValueType::INTEGER;
                break;
            case FRETURN:
                newMethod.returnType = ScriptyValueType::FLOAT;
                break;
            case SRETURN:
                newMethod.returnType = ScriptyValueType::STRING;
                break;
            case ZRETURN:
                DIE << "NOT_IMPLEMENTED()\n";
                break;
            case LRETURN:
                DIE << "NOT_IMPLEMENTED()\n";
                break;           
            case VOIDRETURN:
                newMethod.returnType = ScriptyValueType::NONETYPE;
                break;
            default:
                newMethod.returnType = ScriptyValueType::NONETYPE;
                break;
            }            

            functions.push_back(newMethod); // push the new function to the MethodTable
            break;
        }
        default:
            DIE << "Unknown opcode: " << std::hex << opcode;
            break;
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
    constants.push_back(STRING_("Person"));

    constants.push_back(STRING_("Main"));
    constants.push_back(STRING_("age"));
    constants.push_back(INTEGER_(5));
    constants.push_back(NONE_()); 
    constants.push_back(STRING_("a")); 
    constants.push_back(INTEGER_(2));
    constants.push_back(STRING_("b")); 

    code = {
        SCONST, 0, // class name "person"
        MCLASS, // make a class.
        SCONST, 2, // field name "age"
        ICONST, 3, // field value: 5
        PUTFIELD, // Puts the ICONST, 2, into the class we made.
        ICONST, 4, // Value for a
        SCONST, 5, // parameter name "a"
        ICONST, 6, // Value for b
        SCONST, 7, // parameter name "b"
        SCONST, 1, // Function name "Main".
        MFUNC, 2, // make a function with 2 parameters.
        VOIDRETURN, // MFUNC return type (void)
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
