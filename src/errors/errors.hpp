#ifndef  ERRORS_H
#define ERRORS_H
#include <string>
#include <iostream>
#include <vector>
#include "../tokenizer/token.hpp"
#include "../position/position.hpp"

// Error class used for handling parsing errors.
class ParseError {
public:
    Token token_bef;
    Token token_at;
    std::string error_name;
    std::string details;
    std::string expected;

    ParseError() {}

    ParseError(Token bef, Token at, std::string name, std::string details, std::string expected)
        : token_bef(bef), token_at(at), error_name(name), details(details), expected(expected) {}

    std::string as_string() { // Construct a nice human readable error with strings.
        std::string result = error_name + ": " + details + "\n";
        result += "Unexpected token " + token_bef.type, + ":" + token_bef.value + ", after token: " + token_at.type + ":" + token_at.value + "\n" + "Was expecting: " + expected + "\n";
        return result;
    }
};

class VariableDeclarationError : public ParseError {
public:
    VariableDeclarationError(Token bef, Token at, std::string details, std::string expected)
        : ParseError(bef, at, "Variable Declaration Error", details, expected) {}
};

// Base Error class (mostly used during lexing)
class Error {
public:
    Position pos_start;
    Position pos_end;
    std::string error_name;
    std::string details;

    Error() {}

    Error(Position start, Position end, std::string name, std::string details) // Default error constructor.
        : pos_start(start), pos_end(end), error_name(name), details(details) {} 

    std::string as_string() { // Construct a nice human readable error with strings.
        std::string result = error_name + ": " + details + "\n";
        result += "File " + pos_start.fn + ", line " + std::to_string(pos_start.ln + 1) + "\n";
        return result;
    }
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

// When the user attempts to divide by zero.
class ZeroDivisionError : public Error {
public:
    ZeroDivisionError(Position start, Position end, std::string details)
        : Error(start, end, "Division by Zero is not allowed", details) {}
};

#endif