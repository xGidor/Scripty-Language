#ifndef  PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <vector>
#include "tokenizer.hpp"

class ParseResult {

};

class Parser
{
public:

	std::vector<Token> tokens;
	int token_index = -1;

	void Advance();
	void Reverse(int amount);

	/*
	Parses a string into AST
	*/
	void Parse(std::string text);

	/*
	Main Entry Point
	*/
	void Program();
	
};

#endif