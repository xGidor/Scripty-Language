#include <iostream>
#include <string>
#include "tokenizer.hpp"
#include "parser.hpp"

//std::vector<Token> Run(std::string text);

void run(std::string text);

// Main Program Loop
int main() {

	for (int i = 0; i < 1; i = 0)
	{
		std::string* input;
		input = new std::string;
		std::cout << "Scripty > ";
		std::getline(std::cin, *input);

		run(*input);

		delete input;
	}
	
	return 0;
}

void run(std::string text)
{
	Lexer lex = Lexer("<program>", text);
	LexerResult result = lex.MakeTokens();
	if (result.error.error_name != "NoError")
	{
		std::string errorString = result.error.as_string();
		std::cout << errorString;
		return;
	}
	std::vector<Token> tokens = result.tokens; // get the tokens from the lexical analyzer
	Parser parser = Parser(lex, tokens);
	parser.current_token = parser.Get_Next_Token();
	parser.Parse();

	for (int i = 0; i < tokens.size(); i++) {
		
		std::cout << tokens[i] << " " << std::endl;
	}
}

