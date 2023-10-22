#ifndef  TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <iostream>
#include <vector>
#include "errors.hpp"


// Token types and Digits
const std::string DIGITS = "0123456789";
const std::string INT = "INT";
const std::string FLOAT = "FLOAT";
const std::string STRING = "STRING";
const std::string PLUS = "PLUS";
const std::string MINUS = "MINUS";
const std::string MUL = "MULTIPLY";
const std::string DIV = "DIVINE";
const std::string POW = "POWER";
const std::string LPAREN = "LEFT_PARENTHESIS";
const std::string RPAREN = "RIGHT_PARENTHESIS";
const std::string LCURLY = "LEFT_CURLYBRACKET";
const std::string RCURLY = "RIGHT_CURLYBRACKET";
const std::string EOFILE = "END_OF_FILE";


//Define the Token struct
struct Token
{
public:
	std::string type;
	std::string value;
	Position pos_start;
	Position pos_end;

	Token(std::string type_, std::string value_, Position pos_start);

	friend std::ostream& operator<<(std::ostream& os, const Token& token) {
		os << "Token { Type: " << token.type << ", Value: '" << token.value << "' }";
		return os;
	}
};

// Struct for results from the Lexer
struct LexerResult {
public:
	std::vector<Token> tokens; // Specify the template argument as 'Token'
	Error error;

	LexerResult(std::vector<Token> t, Error e)
		: tokens(t), error(e) {}
};

// Base class of the lexer with function declarations
class Lexer
{
public:
	std::string text; // File text
    std::string fn; // Filename
    Position position = Position(-1, 0, -1, fn, text);
	char current_character = '\0'; // the current character the lexer goes through.

	Lexer(std::string fn_, std::string text_);
	void Advance();
	LexerResult MakeTokens();
	Token MakeNumber();
};


#endif // ! TOKENIZER_H

