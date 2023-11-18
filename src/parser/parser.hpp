#ifndef  PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "../tokenizer/tokenizer.hpp"
#include "../errors/errors.hpp"
#include "../nodes/nodes.hpp"

enum ParsingResult
{
	success_,
	error_,
};

struct ParseResult {
	ParsingResult result;
	ASTNode* node;
	ParseError error;

	ParseResult(ParsingResult l, ASTNode* n)
		: result(l), node(n) {} // Used for successfull parsing operations

	ParseResult(ParsingResult l, ParseError e)
		: result(l), error(e) {} // Used for parsing operations that encounters an error.
};

class Parser
{
public:

	Lexer lex;
	int token_index = -1;
	Token current_token;
	std::vector<Token> token_list;

	Parser(Lexer lexer, std::vector<Token> tokens); // Constructor
	
	//Error error();
	void Eat(std::string token_type);
	Token Get_Next_Token();
	ParseResult Atom();
	ParseResult Factor();
	ParseResult Term();
	ParseResult Expr();
	float evaluateAST(ASTNode* node);
	ParseResult Parse();
	
};

#endif
