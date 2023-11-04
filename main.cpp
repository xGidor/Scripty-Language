#include <iostream>
#include <string>
#include "src/include/tokenizer.hpp"
#include "src/include/parser.hpp"

//std::vector<Token> Run(std::string text);

void run(std::string text);

// Main Program Loop
int main() {

	for (int i = 0; i < 1; i = 0) // Infinite Program Loop
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
	Lexer lex = Lexer("<program>", text); // Create our lexer with a filename (For console it's <program>) and the file contents
	LexerResult lexRes = lex.MakeTokens(); // Make tokens from the file text.

	// Handle LexerResult

	std::vector<Token> tokens = lexRes.tokens; // get the tokens from the lexical analyzer
	Parser parser = Parser(lex, tokens); // Create our Parser Object.
	ASTNode* root = parser.Parse(); // Parse our Lexed tokens and generate a syntax tree.
	int result = parser.evaluateAST(root); // Traverse the Abstract Syntax Tree

	// Handle ParseResult

	std::cout << result << std::endl;




	// Debug Stuff
	//for (int i = 0; i < tokens.size(); i++) 
	//{
	//	std::cout << tokens[i] << " " << std::endl;
	//}

}

