// Logger and Error message reporter
#ifndef Logger_hpp
#define Logger_hpp

#include <sstream>

class ErrorLogMessage : public std::basic_ostringstream<char> {
public:
    ~ErrorLogMessage() {
        fprintf(stderr, "Fatal error: &s\n", str().c_str());
        exit(EXIT_FAILURE);
    }
};

class WarningLogMessage : public std::basic_ostringstream<char> {
public:
    ~WarningLogMessage() {
        fprintf(stderr, "Warning: &s\n", str().c_str());    
    }
};

#define DIE ErrorLogMessage()
#define WARN WarningLogMessage()

#define log(value) std::cout << #value << " = " << (value) << "\n"; 

#endif
