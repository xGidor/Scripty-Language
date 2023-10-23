#include <string>
#include "parser.hpp"

Parser::Parser(Lexer lexer, std::vector<Token> tokens)
{
	lex = lexer;
    token_list = tokens;
}

void Parser::Eat(std::string token_type) 
{   
	if (current_token.type == token_type) {
		current_token = Get_Next_Token();
	}
	else {
		//error();
	}
}
Token Parser::Get_Next_Token()
{
    token_index++;
    return token_list[token_index];
}

ASTNode Parser::Factor() {
    Token token = current_token;
    std::cout << current_token.type;
    std::cout << token_index << std::endl;
    if (token.type == FLOAT) {
        Eat(FLOAT);

        std::cout << "parsed float node\n";
        return NumberNode(std::stof(token.value));
    }
    if (token.type == INT) {
        Eat(INT);

        std::cout << "parsed int node\n";
        return NumberNode(std::stoi(token.value));
    }
    if (token.type == LPAREN) {
        Eat(LPAREN);
        ASTNode node = Expr();
        Eat(RPAREN);
        return node;
    }
}

ASTNode Parser::Term() {
    ASTNode node;
    ASTNode l_node = Factor();
    while (current_token.type == MUL || current_token.type == DIV) {
        Token token = current_token;
        if (token.type == MUL) {
            Eat(MUL);
        }
        else if (token.type == DIV) {
            Eat(DIV);
        }

        std::cout << "parsed binarynode\n";
        node = BinaryOpNode(token, l_node, Factor());
    }
    std::cout << "parsed term\n";
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

        std::cout << "parsed binary node\n";
        node = BinaryOpNode(token, node, Term());
    }

    std::cout << "parsed expr\n";
    return node;
}

ASTNode Parser::parse() {
    return Expr();
}