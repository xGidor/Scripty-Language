#ifndef  PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "../tokenizer/tokenizer.hpp"
#include "../errors/errors.hpp"
#include "../nodes/nodes.hpp"

class ParseResult {

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
	ASTNode* Primary();
	ASTNode* Factor();
	ASTNode* Term();
	ASTNode* Expr();
	float evaluateAST(ASTNode* node);
	ASTNode* Parse();
	
};

#endif
