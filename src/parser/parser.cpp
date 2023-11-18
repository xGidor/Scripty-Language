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
        //std::cout << current_token.type << '\n'; // Print out the token type for debug purposes.
	}
	else {
		//error();
	}
}

// Gets the next token from the token_list and advances the token index
Token Parser::Get_Next_Token()
{
    token_index++; // Increase the token index so we can keep track of our position in the list.
    return token_list[token_index]; // Return the current token at our position.
}

ParseResult Parser::Atom() {
    Token token = current_token; // Set the local token to the current token.

    if (token.type == KEYWORD_)
    {   
        Token varType = token;
        Eat(KEYWORD_);

        if (current_token.type == IDENTIFIER)
        {
            Token varName = current_token;
            Eat(IDENTIFIER);
            if (current_token.type != EQUALS)
            {
                if (current_token.type == NEW_LINE || current_token.type == EOFILE)
                {
                    ASTNode* node_ = VarAccessNode::createVariableAccessNode(varName);
                    ParseResult result = ParseResult(success_, node_);
                    return result;
                }
                ParseError err = VariableDeclarationError(varName, current_token, "Got unexpected token", "'=' or ';'");
                ParseResult result = ParseResult(error_, err);
                return result;
            }
            Token currentEq = current_token;
            Eat(EQUALS);
            if (current_token.type != INT && current_token.type != FLOAT && current_token.type != STRING && current_token.type != EOFILE)
            {
                ParseError err = VariableDeclarationError(currentEq, current_token, "Got unexpected token", "value types: integer, string or float");
                ParseResult result = ParseResult(error_, err);
                return result;
            }
            ASTNode* expression = Expr().node; // Parse the expression to be assigned
            // Create a VariableAssignNode using the variable name and the expression
            ASTNode* node_ = VarAssignNode::createVariableAssignNode(varName, expression);  
            ParseResult result = ParseResult(success_, node_);
            return result;
        }

        ParseError err = VariableDeclarationError(varType, current_token, "Got unexpected token", "an Identifier");
        ParseResult result = ParseResult(error_, err);
        return result;

    } else if (token.type == IDENTIFIER) {
        Token varName_ = token;
        Eat(IDENTIFIER);
        if (current_token.type != EQUALS)
        {
            if (current_token.type == NEW_LINE || current_token.type == EOFILE)
            {
                ASTNode* node_ = VarAccessNode::createVariableAccessNode(varName_);
                ParseResult result = ParseResult(success_, node_);
                return result;
            }
            ParseError err = VariableDeclarationError(varName_, current_token, "Got unexpected token", "'=' or ';'");
            ParseResult result = ParseResult(error_, err);
            return result;
        }
        Token currentEq = current_token;
        Eat(EQUALS);
        if (current_token.type != INT && current_token.type != FLOAT && current_token.type != STRING && current_token.type != EOFILE)
        {
            ParseError err = VariableDeclarationError(currentEq, current_token, "Got unexpected token", "value types: integer, string or float");
            ParseResult result = ParseResult(error_, err);
            return result;
        }
        ASTNode* expression = Expr().node; // Parse the expression to be assigned
        // Create a VariableAssignNode using the variable name and the expression
        ASTNode* node_ = VarAssignNode::createVariableAssignNode(varName_, expression);
        ParseResult result = ParseResult(success_, node_);
        return result;
    }

    if (token.type == FLOAT) { // Check if our current token is a float
        Eat(FLOAT);
        ASTNode* node_ = NumberNode::createNumberNodeFloat(token); // Create a float Numbernode
        ParseResult result = ParseResult(success_, node_);
        return result;
    }
    if (token.type == INT) {  // Check if our current token is a integer
        Eat(INT);
        ASTNode* node_ = NumberNode::createNumberNodeInt(token); // Create an integer Numbernode
        ParseResult result = ParseResult(success_, node_);
        return result;
    }
    if (token.type == LPAREN) {  // Check if our current token is a left parenthesis
        Eat(LPAREN); 
        ASTNode* node = Expr().node; // Create an expression check with the parenthesis.
        Eat(RPAREN);
        ParseResult result = ParseResult(success_, node);
        return result;
    }
    // Handle other cases or raise an error for invalid input.
    ParseError err = UnknownParsingError(current_token, Token("None", "None", lex.position), "Got unexpected token", "'Variable Declaration', 'Variable Access', 'integer', 'float' or a 'string'");
    ParseResult result = ParseResult(error_, err);
    return result;
}
ParseResult Parser::Factor() {
    ParseResult res = Atom(); // Get our numbers or parenthesis expression
    if(CheckErrors(res))
    {
    ASTNode* node = res.node;
    while (current_token.type == MUL || current_token.type == DIV) { // check for our multiplication or division tokens.
        Token token = current_token; // Set the local token to the current token.
        if (token.type == MUL) { // Check if our current token is a multiplication
            Eat(MUL);
        }
        else if (token.type == DIV) { // Check if our current token is a civision
            Eat(DIV);
        }
        ASTNode* right = Atom().node; // Create another number and create a binary operation node
        node = BinaryOpNode::createBinaryOpNode(token, node, right);
    }
    ParseResult result = ParseResult(success_, node);
    return result;
    }
}
ParseResult Parser::Term() {
    ParseResult res = Factor();
    if(CheckErrors(res))
    {
    ASTNode* node = res.node;
    
    while (current_token.type == PLUS || current_token.type == MINUS) { // check for our addition or subtraction tokens.
        Token token = current_token; // Set the local token to the current token.
        if (token.type == PLUS) { // Check if our current token is a addition
            Eat(PLUS);
        }
        else if (token.type == MINUS) { // Check if our current token is a subtraction
            Eat(MINUS);
        }
        ASTNode* right = Factor().node; // Create another Binary Operation node or a numbernode and use it in this one.
        node = BinaryOpNode::createBinaryOpNode(token, node, right);
    }
    ParseResult result = ParseResult(success_, node);
    return result;
    }
}

ParseResult Parser::Expr() {
    return Term(); 
}
    
ParseResult Parser::Parse() {
    current_token = Get_Next_Token(); // Get the first token of the file.
    return Expr(); // Start the parser with an expression lookup.
}


float Parser::evaluateAST(ASTNode* node) { // Traverse the nodes.
    if (node->getType() == BINARY_OP_NODE) {
        BinaryOpNode* binaryOp = static_cast<BinaryOpNode*>(node); // Get the type of the inherited class using a static cast. If its a binary op node continue.
        float leftValue = evaluateAST(binaryOp->getLeft()); // Evaluates the left node of the Binary OP Node and gets its value using this function
        float rightValue = evaluateAST(binaryOp->getRight()); // Evaluates the right node of the Binary OP Node and gets its value using this function
        if (binaryOp->getOperator().type == PLUS) { // Check if the binary operation has a plus operator
            return leftValue + rightValue; // Execute the addition
        }
        else if (binaryOp->getOperator().type == MINUS) { // Check if the binary operation has a minus operator
            return leftValue - rightValue; // Execute the subtraction
        }
        else if (binaryOp->getOperator().type == MUL) { // Check if the binary operation has a multiply operator
            return leftValue * rightValue; // Execute the multiplication
        }
        else if (binaryOp->getOperator().type == DIV) { // Check if the binary operation has a division operator
            if (leftValue == 0 || rightValue == 0) // Check if we divide with zero
            {
                return 0; // Handle division with zero by returning zero
            }
            
            return leftValue / rightValue; // Execute division if we don't divide with zero.
        }
    }
    else if (node->getType() == NUMBER_NODE) { // If current node is a numbernode then get the node type class with a static cast.
        NumberNode* numberNode = static_cast<NumberNode*>(node); 
        return numberNode->getValue(); // Return the numbernode value.
    }
    return 0; // Handle other node types as needed.
}
