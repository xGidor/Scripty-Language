#include <iostream>
#include "src/tokenizer/tokenizer.hpp"
#include "src/parser/parser.hpp"

using std::string, std::cout, std::getline;

//std::vector<Token> Run(std::string text);

void run(string text);

// Main Program Loop
int main() {

	for (;;) // Infinite Program Loop
	{
		string* input;
		input = new string;
		cout << "Scripty > ";
		getline(std::cin, *input);

		run(*input);

		delete input;
	}
	
	return 0;
}

int LexerCheck(LexerResult result) // Function for checking errors during lexing.
{	
	if (result.result == LexResult::success) // Checks if the Lexing Result was a success
		return 1; // Return True
	
	cout << result.error.as_string(); // Generate the error message if it was not a success.
	return 0; // Return false
}


void run(string text)
{
	Lexer lex = Lexer("<program>", text); // Create our lexer with a filename (For console it's <program>) and the file contents
	LexerResult lexResult = lex.MakeTokens(); // Make tokens from the file text.

	if (LexerCheck(lexResult) == 0) { return; } // Check for errors during lexing process.

	Parser parser = Parser(lex, lexResult.tokens); // Create our Parser Object.
	ASTNode* root = parser.Parse(); // Parse our Lexed tokens and generate a syntax tree.
	float result = parser.evaluateAST(root); // Traverse the Abstract Syntax Tree

	// Handle ParseResult

	cout << result << '\n';




	// Debug Stuff
	for (int i = 0; i < lexResult.tokens.size(); i++) 
	{
		cout << lexResult.tokens[i] << " \n";
	}

}

