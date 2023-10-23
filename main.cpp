#include <iostream>
#include <string>
#include "tokenizer.hpp"


std::vector<Token> Run(std::string text);

// Main Program Loop
int main() {

	for (int i = 0; i < 1; i = 0)
	{
		std::string* input;
		input = new std::string;
		std::cout << "Scripty > ";
		std::getline(std::cin, *input);

		std::vector<Token> tokens = Run(*input);

		for (int i = 0; i < tokens.size(); i++) {
			std::cout << tokens[i] << " " << std::endl;
		}

		delete input;
	}
	
	return 0;
}

std::vector<Token> Run(std::string text)
{
	Lexer lex = Lexer("<program>", text);
	//LexerResult result = lex.MakeTokens();
	//if (result.error.error_name == "NoError")
	//{
	//	return result.tokens;
	//}
	//result.tokens.clear(); // Clear the tokens as we can't use them due to an error.
	//std::string errorString = result.error.as_string(); //  Convert the error object to readable string format.
	//std::cout << "\n" << errorString + "\n";
	//return result.tokens; // Return an empty list so we don't get an error.
}

