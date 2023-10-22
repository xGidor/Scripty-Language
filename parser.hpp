#ifndef  PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <vector>

class Parser
{
public:
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