#ifndef  ERRORS_H
#define ERRORS_H
#include <string>
#include <iostream>
#include <vector>

#include "position.hpp"

// Base Error class
class Error {
public:
    Position pos_start;
    Position pos_end;
    std::string error_name;
    std::string details;

    Error(Position start, Position end, std::string name, std::string details) // Default error constructor.
        : pos_start(start), pos_end(end), error_name(name), details(details) {} 

    std::string as_string() { // Construct a nice human readable error with strings.
        std::string result = error_name + ": " + details + "\n";
        result += "File " + pos_start.fn + ", line " + std::to_string(pos_start.ln + 1);
        return result;
    }
};

// Error class used for Success Operations on the lexer..
class NoError : public Error {
public:
    NoError(Position start, Position end, std::string details)
        : Error(start, end, "NoError", details) {}
};

// When the lexer identifies an illegal character throw this error.
class IllegalCharacterError : public Error {
public:
    IllegalCharacterError(Position start, Position end, std::string details)
        : Error(start, end, "Illegal Character", details) {}
};

// When a syntax error happens fire this.
class InvalidSyntaxError : public Error {
public:
    InvalidSyntaxError(Position start, Position end, std::string details)
        : Error(start, end, "Invalid Syntax", details) {}
};

#endif