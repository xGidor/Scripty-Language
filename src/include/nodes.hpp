#include <iostream>
#include <vector>
#include "json.hpp" // C++ Json lib
#include "tokenizer.hpp"

using json = nlohmann::json;



// Define ASTVisitor class
//class ASTVisitor {
//public:
//    void visitVariableDeclaration(VariableDeclarationNode node);
//    void visitFunctionCall(FunctionCallNode node);
//    void visitExpression(ExpressionNode node);
//};


class ASTNode {
public:
    virtual json serialize() const = 0;
};

class StringNode : public ASTNode {
    std::string value;

    json serialize() const override {
        json j;
        j["type"] = "String";
        j["value"] = value;
        return j;
    }
    StringNode(std::string text);
};

class NumberNode : public ASTNode { // Inherit the ASTNode class
public:
    float value; // The value of the number node.

    NumberNode(float val) : value(val) {}

    json serialize() const override {
        json j;
        j["type"] = "Number";
        j["value"] = value;
        return j;
    }

    static NumberNode* createNumberNodeFloat(const Token& token) {
        return new NumberNode(std::stof(token.value));
    }

    static NumberNode* createNumberNodeInt(const Token& token) {
        return new NumberNode(std::stoi(token.value));
    }
    float evaluate() { return value; }

    NumberNode add(const NumberNode& other) const;
    NumberNode subtract(const NumberNode& other) const;
    NumberNode multiply(const NumberNode& other) const;
    NumberNode divide(const NumberNode& other) const;
};


class UnaryOpNode : public ASTNode {
public:
    Token op;
    ASTNode* op_node;

    json serialize() const override {
        json j;
        j["type"] = "UnaryOP";
        j["node"] = op_node->serialize();
        return j;
    }

    static UnaryOpNode* createUnaryOpNode(Token op_token, ASTNode* node) {
        return new UnaryOpNode(op_token, node);
    }

    UnaryOpNode(Token operator_token, ASTNode* node) : op(operator_token), op_node(node) {}

};

class BinaryOpNode : public ASTNode {
public:
    Token op; // The operation token, can be plus, minus etc...
    ASTNode* left; // The left AST node of the operation
    ASTNode* right; // THe right AST node of the operation

    json serialize() const override {
        json j;
        j["type"] = "BinaryOp";
        j["operator"] = op.type;
        j["left"] = left->serialize();
        j["right"] = right->serialize();
        return j;
    }
    static BinaryOpNode* createBinaryOpNode(Token op_token, ASTNode* left, ASTNode* right) {
        return new BinaryOpNode(op_token, left, right);
    }

    BinaryOpNode(Token operator_token, ASTNode* leftnode, ASTNode* rightnode) : op(operator_token), left(leftnode), right(rightnode) {}

};
