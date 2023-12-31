#include <iostream>
#include <vector>
#include <stack>

#include "values.h"

// Variable Struct
struct ScriptyVariable {
    std::string name;       // The name of the variable
    ScriptyValue value;    // The value of the variable
    ScriptyValueType type; // The type of the parameter (even tho its stored in the scriptyValue its good to also have it here)
};

// Value Parameters
struct ScriptyParameter {
    std::string name;  // The name of the parameter
    ScriptyValueType type;  // The data type of the parameter
    ScriptyValue defaultValue; // The default value of the parameter
};

// Function Type definition
struct ScriptyFunction {
    std::string name; // The name of the function
    std::vector<ScriptyParameter> parameters; // The parameters of the function
    ScriptyValueType returnType; // default func (void in other languages)
};

// Class Type Definition
struct ScriptyClass {
    std::string name; // The name of the class
    std::vector<ScriptyFunction> methods; // The functions the class holds.
    std::vector<ScriptyVariable> fields; // Parameters of the class
    ScriptyFunction constructor; // The constructor method of the class
    ScriptyFunction deconstructor; // The deconstructor method of the class
};


struct Frame {
    // Local variables, including parameters
    std::vector<ScriptyVariable> localVars;

    // Constructor to initialize the frame
    Frame(int LocalVars) : localVars(LocalVars) {
        // Initialize frame related data here
    }
};