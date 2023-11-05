#ifndef  TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "../errors/errors.hpp"

enum LexResult
{
	success,
	error,
};

// Token types and Digits
const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const std::string DIGITS = "0123456789";
const std::string LETTERS_DIGITS = LETTERS + DIGITS;

const std::string IDENTIFIER = "IDENTIFIER";
const std::string KEYWORD_ = "KEYWORD";
const std::string INT = "INT";
const std::string FLOAT = "FLOAT";
const std::string STRING = "STRING";
const std::string PLUS = "PLUS";
const std::string MINUS = "MINUS";
const std::string MUL = "MULTIPLY";
const std::string DIV = "DIVIDE";
const std::string POW = "POWER";
const std::string EQUALS = "EQUALS";
const std::string NOT_EQUALS = "NOT_EQUALS";
const std::string EQUALS_EQUALS = "EQUALS_EQUALS";
const std::string LESS_THAN = "LESS_THAN";
const std::string GREATER_THAN = "GREATER_THAN";
const std::string LT_EQUALS = "LESS_THAN_OR_EQUALS";
const std::string GT_EQUALS = "GREATER_THAN_OR_EQUALS";
const std::string LPAREN = "LEFT_PARENTHESIS";
const std::string RPAREN = "RIGHT_PARENTHESIS";
const std::string LCURLY = "LEFT_CURLYBRACKET";
const std::string RCURLY = "RIGHT_CURLYBRACKET";
const std::string EOFILE = "END_OF_FILE";
const std::string TOKEN_ERROR = "INVALID_TOKEN";

const std::set<std::string> KEYWORD = {
	"let",
	"int",
	"float",
	"string",
	"if",
	"else",
	"elif",
	"function",
	"break",
	"return",
	"for",
	"while",
	"continue"
};

//Define the Token struct
class Token
{
public:
	std::string type;
	std::string value;
	Position pos_start;
	Position pos_end;
	Token() {} // Add a default constructor so Token can be used with Node classes
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
	LexResult result;
	Error error;

	LexerResult(std::vector<Token> t, LexResult l)
		: tokens(t), result(l) {}

	LexerResult(LexResult l, Error e)
		: result(l), error(e) {}
};

// Base class of the lexer with function declarations
class Lexer
{
public:
	std::string text; // File text
    std::string fn; // Filename
    Position position = Position(-1, 0, -1, fn, text);
	char current_character = '\0'; // the current character the lexer goes through.
	Lexer();
	Lexer(std::string fn_, std::string text_);
	void Advance();
	LexerResult MakeTokens();
	Token MakeNumber();
	Token MakeIdentifier();
	Token MakeEquals();
	Token makeString(char qt);
};


#endif // ! TOKENIZER_H

