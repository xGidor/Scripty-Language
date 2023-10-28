#include <string>
#include "include/parser.hpp"

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

ASTNode* Parser::Primary() {
    Token token = current_token;
    if (token.type == FLOAT) {
        Eat(FLOAT);
        return NumberNode::createNumberNodeFloat(token);
    }
    if (token.type == INT) {
        Eat(INT);
        return NumberNode::createNumberNodeInt(token);
    }
    if (token.type == LPAREN) {
        Eat(LPAREN);
        ASTNode* node = Expr();
        Eat(RPAREN);
        return node;
    }
    // Handle other cases or raise an error for invalid input.
    return nullptr; // Handle this case as needed.
}
ASTNode* Parser::Factor() {
    ASTNode* node = Primary();
    while (current_token.type == MUL || current_token.type == DIV) {
        Token token = current_token;
        if (token.type == MUL) {
            Eat(MUL);
        }
        else if (token.type == DIV) {
            Eat(DIV);
        }
        ASTNode* right = Primary();
        node = BinaryOpNode::createBinaryOpNode(token, node, right);
    }
    return node;
}
ASTNode* Parser::Term() {
    ASTNode* node = Factor();
    while (current_token.type == PLUS || current_token.type == MINUS) {
        Token token = current_token;
        if (token.type == PLUS) {
            Eat(PLUS);
        }
        else if (token.type == MINUS) {
            Eat(MINUS);
        }
        ASTNode* right = Factor();
        node = BinaryOpNode::createBinaryOpNode(token, node, right);
    }
    return node;
}

float Parser::ParseAndCalculate() {
    ASTNode* root = Parse();
    if (root) {
        // Attempt to cast the root to a NumberNode
        NumberNode* numberNode = dynamic_cast<NumberNode*>(root);
        BinaryOpNode* binNode = dynamic_cast<BinaryOpNode*>(root);


        if (numberNode) {
            return static_cast<float>(numberNode->value);
        }
        else if (binNode)
        {
            return static_cast<float>(binNode->evaluate());
        }
        else {
            std::cout << "asd";
            // Handle the case where the root is not a NumberNode.
            // You can raise an exception or handle it as needed.
            return 0.0f; // Handle this case as needed.
        }
    }
    else {
        // Handle the case where parsing failed or return an error value.
        return 0.0f; // Handle this case as needed.
    }
}

ASTNode* Parser::Expr() {
    return Term();
}
    
ASTNode* Parser::Parse() {
    return Expr(); // Start the parser with an expression lookup.
}
