#ifndef  ERRORS_H
#define ERRORS_H
#include <string>
#include <iostream>
#include <vector>

#include "position.hpp"

class Error {
public:
    Position pos_start;
    Position pos_end;
    std::string error_name;
    std::string details;

    Error(Position start, Position end, std::string name, std::string details)
        : pos_start(start), pos_end(end), error_name(name), details(details) {}

    std::string as_string() {
        std::string result = error_name + ": " + details + "\n";
        result += "File " + pos_start.fn + ", line " + std::to_string(pos_start.ln + 1);
        return result;
    }
};

class NoError : public Error {
public:
    NoError(Position start, Position end, std::string details)
        : Error(start, end, "NoError", details) {}
};

class IllegalCharacterError : public Error {
public:
    IllegalCharacterError(Position start, Position end, std::string details)
        : Error(start, end, "Illegal Character", details) {}
};

class InvalidSyntaxError : public Error {
public:
    InvalidSyntaxError(Position start, Position end, std::string details)
        : Error(start, end, "Invalid Syntax", details) {}
};

#endif