#include <string>
#include "parser.hpp"
#include "nodes.hpp"

Parser::Parser(Lexer lexer)
{
	lex = lexer;
}

void Parser::Eat(std::string token_type) 
{
	if (current_token.type == token_type) {
		current_token = lex.Get_Next_Token();
	}
	else {
		//error();
	}
}


ASTNode Parser::Factor() {
    Token token = current_token;
    if (token.type == FLOAT) {
        Eat(FLOAT);
        return NumberNode(std::stof(token.value));
    }
    else if (token.type == LPAREN) {
        Eat(LPAREN);
        ASTNode node = Expr();
        Eat(RPAREN);
        return node;
    }
    return;
}

ASTNode Parser::Term() {
    ASTNode node = Factor();
    while (current_token.type == MUL || current_token.type == DIV) {
        Token token = current_token;
        if (token.type == MUL) {
            Eat(MUL);
        }
        else if (token.type == DIV) {
            Eat(DIV);
        }
        node = BinaryOpNode(token, node, Factor());
    }
    return node;
}

ASTNode Parser::Expr() {
    ASTNode node = Term();
    while (current_token.type == PLUS || current_token.type == MINUS) {
        Token token = current_token;
        if (token.type == PLUS) {
            Eat(PLUS);
        }
        else if (token.type == MINUS) {
            Eat(MINUS);
        }
        node = BinaryOpNode(token, node, Term());
    }
    return node;
}

ASTNode Parser::parse() {
    return Expr();
}