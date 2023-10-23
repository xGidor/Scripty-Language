#include <iostream>
#include <vector>
//#include "json.hpp" // C++ Json lib
#include "tokenizer.hpp"

//using json = nlohmann::json;



// Define ASTVisitor class
class ASTVisitor {
public:
    void visitVariableDeclaration(VariableDeclarationNode node);
    void visitFunctionCall(FunctionCallNode node);
    void visitExpression(ExpressionNode node);
};


class ASTNode {

};

class StringNode : public ASTNode {
    std::string value;

    StringNode(std::string text);
};

class VariableDeclarationNode : public ASTNode {
};

class FunctionCallNode : public ASTNode {
};

class ExpressionNode : public ASTNode {
public:
    std::vector<ASTNode*> children;
};

class NumberNode : public ASTNode { // Inherit the ASTNode class
public:
    float value; // The value of the number node.
    
    NumberNode(float value);

    NumberNode add(const NumberNode& other) const;
    NumberNode subtract(const NumberNode& other) const;
    NumberNode multiply(const NumberNode& other) const;
    NumberNode divide(const NumberNode& other) const;
};


class UnaryOpNode : public ASTNode {
public:
    Token op;
    ASTNode* op_node;

    UnaryOpNode(Token operator_token, ASTNode node);


};

class BinaryOpNode : public ASTNode {
public:
    Token op; // The operation token, can be plus, minus etc...
    ASTNode left; // The left AST node of the operation
    ASTNode right; // THe right AST node of the operation

    BinaryOpNode(Token operator_token, ASTNode leftnode, ASTNode rightnode);

};


void asd() {
    // Create the AST by parsing your programming language

    // Serialize the root node to JSON
   // ASTNode* root = /* your root node */
    //json astJson = root->serialize();

    // Print the JSON representation of the AST
    //std::cout << astJson.dump(2) << std::endl;

  //  return 0;
}
