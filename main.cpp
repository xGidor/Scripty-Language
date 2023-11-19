#include <iostream>
#include <string>
#include "src/tokenizer/tokenizer.hpp"
#include "src/parser/parser.hpp"

//std::vector<Token> Run(std::string text);

void run(std::string text);

// Main Program Loop
int main() {

	for (;;) // Infinite Program Loop
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

// Check if there was an error during the Lexing proccess
int LexerCheck(LexerResult result) // Function for checking errors during lexing.
{	
	if (result.result == LexResult::success) // Checks if the Lexing Result was a success
		return 1; // Return True

	std::cout << result.error.as_string(); // Generate the error message if it was not a success.
	return 0; // Return false
}

void run(std::string text)
{
	Lexer lex = Lexer("<program>", text); // Create our lexer with a filename (For console it's <program>) and the file contents
	LexerResult lexResult = lex.MakeTokens(); // Make tokens from the file text.
	if (LexerCheck(lexResult) == 0) { return; } // Check for errors during lexing process.
	Parser parser = Parser(lex, lexResult.tokens); // Create our Parser Object.
	ParseResult root = parser.Parse(); // Parse our Lexed tokens and generate a syntax tree.

	float result = parser.evaluateAST(root.node); // Traverse the Abstract Syntax Tree
		
	std::cout << result << "\n";;

	// Debug Stuff
	for (int i = 0; i < lexResult.tokens.size(); i++) 
	{
		std::cout << lexResult.tokens[i] << " " << "\n";
	}
}