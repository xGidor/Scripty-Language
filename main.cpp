#include <iostream>
#include <string>
#include "src/include/tokenizer.hpp"
#include "src/include/parser.hpp"

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
	LexerResult lexRes = lex.MakeTokens();
	//if (result.error.error_name != "NoError")
	//{
	//	std::string errorString = result.error.as_string();
	//	std::cout << errorString;
	//	return;
	//}
	std::vector<Token> tokens = lexRes.tokens; // get the tokens from the lexical analyzer
	Parser parser = Parser(lex, tokens); 
	ASTNode* root = parser.Parse();
	int result = parser.evaluateAST(root);
	std::cout << result << std::endl;
	//for (int i = 0; i < tokens.size(); i++) 
	//{
	//	std::cout << tokens[i] << " " << std::endl;
	//}

}

