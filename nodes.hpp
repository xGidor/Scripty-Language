#include <iostream>
#include <vector>
#include "json.hpp" // C++ Json lib
#include "tokenizer.hpp"

using json = nlohmann::json;

class ASTNode {
public:
    virtual json serialize() const = 0;
};

class NumberNode : public ASTNode { // Inherit the ASTNode class
public:
    float value; // The value of the number node.

    NumberNode(float value);

    json serialize() const override {
        json n;
        n["type"] = "Number"; // The type of the node
        n["value"] = value; // The value of the number node
        return n; // return the n (number) node
    }
};

class UnaryOpNode : public ASTNode {
public:
    Token op;
    ASTNode* op_node;

    UnaryOpNode(Token operator_token, ASTNode* node);

    json serialize() const override {
        json una;
        una["type"] = "UnaryOperation";
        una["operator"] = op.type;
        una["node"] = op_node->serialize();
        return una;
    }
};

class BinaryOpNode : public ASTNode {
public:
    Token op; // The operation token, can be plus, minus etc...
    ASTNode* left; // The left AST node of the operation
    ASTNode* right; // THe right AST node of the operation

    BinaryOpNode(Token operator_token, ASTNode* leftnode, ASTNode* rightnode);

    json serialize() const override {
        json bin;
        bin["type"] = "BinaryOperation"; // The type of the node
        bin["operator"] = op.type; // OP Token
        bin["left"] = left->serialize();
        bin["right"] = right->serialize();
        return bin; // return the operation node.
    }
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
