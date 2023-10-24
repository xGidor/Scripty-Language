#include <string>
#include "parser.hpp"

// Base constructor for the Parser class.
Parser::Parser(Lexer lexer, std::vector<Token> tokens)
{
	lex = lexer;
    token_list = tokens;
}

// Verifies tokens.
void Parser::Eat(std::string token_type) 
{   
	if (current_token.type == token_type) { // Verifies the current token to be the one passed into our function
		current_token = Get_Next_Token(); // Get the next token if we could verify the correct token.
        std::cout << current_token.type << std::endl; // Print out the token type for debug purposes.
	}
	else {
		//error();
	}
}

// Gets the next token from the token_list and advances the token index
Token Parser::Get_Next_Token()
{
    token_index++;
    return token_list[token_index];
}

ASTNode* Parser::Factor() {
    Token token = current_token;
    if (token.type == FLOAT) { // check if the current token is a float
        Eat(FLOAT);

        std::cout << "parsed float node\n";
        return NumberNode::createNumberNodeFloat(token); // Create a number node from a float
    }
    if (token.type == INT) {  // check if the current token is an int
        Eat(INT);

        std::cout << "parsed int node\n";
        return NumberNode::createNumberNodeInt(token); // Create a number node from an int
    }
    if (token.type == LPAREN) { // if we have a parenthesis construct an expression
        Eat(LPAREN);// check if the current token is still a LPAREN
        ASTNode* node = Expr(); // construct an expression then advance the parser to the next token
        Eat(RPAREN); // check if the current token is a right parenthesis
        return node;
    }
}

ASTNode* Parser::Term() {
    ASTNode* node = nullptr; // Set it to nullpointer so we don't get an error on the return none; this might lead to issues in the future
    ASTNode* l_node = Factor();
    while (current_token.type == MUL || current_token.type == DIV) {
        Token token = current_token;
        if (token.type == MUL) { // Check if the current token is a MULTIPLICATION
            Eat(MUL);
        }
        else if (token.type == DIV) { // Check if the current token is a DIVISION
            Eat(DIV);
        }

        std::cout << "parsed binary node\n";
        node = BinaryOpNode::createBinaryOpNode(token, l_node, Factor()); // Create a binary node with the got results.
    }
    return node;
}

ASTNode* Parser::Expr() {
    ASTNode* node = Term();
    while (current_token.type == PLUS || current_token.type == MINUS) {
        Token token = current_token;
        if (token.type == PLUS) { // Check if the current token is a PLUS
            Eat(PLUS);
        }
        else if (token.type == MINUS) { // Check if the current token is a MINUS
            Eat(MINUS);
        }

        std::cout << "parsed binary node\n";
        node = BinaryOpNode::createBinaryOpNode(token, node, Term()); // Create a binary node with the got results.
    }

    return node; // Return our newly made BinaryOp Node
}

ASTNode* Parser::Parse() {
    return Expr(); // Start the parser with an expression lookup.
}