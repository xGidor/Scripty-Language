#ifndef  PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "tokenizer.hpp"
#include "errors.hpp"
#include "nodes.hpp"

class ParseResult {

};

class Parser
{
public:

	Lexer lex;
	Token current_token;
	Parser(Lexer lexer);
	
	//Error error();
	void Eat(std::string token_type);
	ASTNode Factor();
	ASTNode Term();
	ASTNode Expr();
	ASTNode parse();

	
};

#endif