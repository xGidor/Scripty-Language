#include <iostream>
#include <vector>
#include "json.hpp" // C++ Json lib
#include "tokenizer.hpp"

using json = nlohmann::json;

class ASTNode {

};

class StringNode : public ASTNode {
    std::string value;

    StringNode(std::string text);
};

class IntNode : public ASTNode { // Inherit the ASTNode class
public:
    int value; // The value of the number node.
    
    IntNode(int value);

    IntNode add(const IntNode& other) const;
    IntNode subtract(const IntNode& other) const;
    IntNode multiply(const IntNode& other) const;
    IntNode divide(const IntNode& other) const;
};

class FloatNode : public ASTNode { // Inherit the ASTNode class
public:
    float value; // The value of the number node.

    FloatNode(float value);

    FloatNode add(const  FloatNode& other) const;
    FloatNode subtract(const  FloatNode& other) const;
    FloatNode multiply(const  FloatNode& other) const;
    FloatNode divide(const  FloatNode& other) const;
};

class UnaryOpNode : public ASTNode {
public:
    Token op;
    ASTNode op_node;

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
