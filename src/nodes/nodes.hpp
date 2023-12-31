#include <iostream>
#include <vector>
#include "../json/json.hpp" // C++ Json lib
#include "../tokenizer/tokenizer.hpp"
#include "../vm/types.h"
#include "../vm/values.h"

using json = nlohmann::json;



// Define ASTVisitor class
//class ASTVisitor {
//public:
//    void visitVariableDeclaration(VariableDeclarationNode node);
//    void visitFunctionCall(FunctionCallNode node);
//    void visitExpression(ExpressionNode node);
//};

enum ASTNodeType {
    NUMBER_NODE,
    STRING_NODE,
    UNARY_OP_NODE,
    BINARY_OP_NODE,
    VAR_ASSIGN_NODE,
    VAR_ACCESS_NODE,
    IF_NODE,
    // Add other node types as needed
};

class ASTNode {
public:
    ASTNodeType nodeType;
    virtual json serialize() const = 0;

    ASTNode() {}; // default Constructor for ASTNode
    ASTNode(ASTNodeType type) : nodeType(type) {} // Parser Constructor for ASTNode

    ASTNodeType getType() {
        return nodeType; // Return the current node type
    } 
};

class VarAccessNode : public ASTNode {
public:
    Token var_name_token; // Identifier Token

    json serialize() const override {
        json j;
        j["type"] = "VarAccess";
        j["name"] = var_name_token.value;
        return j;
    } 

    static VarAccessNode* createVariableAccessNode(Token tok) {
        return new VarAccessNode(tok);
    }

    VarAccessNode(Token tok) : ASTNode(VAR_ACCESS_NODE), var_name_token(tok) {}
};

class IfNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* true_branch;
    ASTNode* false_branch;

    json serialize() const override {
        json j;
        j["type"] = "If";
        j["condition"] = condition->serialize();
        j["true_branch"] = true_branch->serialize();
        if (false_branch != nullptr) {
            j["false_branch"] = false_branch->serialize();
        }
        return j;
    }

    static IfNode* createIfNode(ASTNode* cond, ASTNode* trueBranch, ASTNode* falseBranch = nullptr) {
        return new IfNode(cond, trueBranch, falseBranch);
    }

    IfNode(ASTNode* cond, ASTNode* trueBranch, ASTNode* falseBranch = nullptr)
        : ASTNode(IF_NODE), condition(cond), true_branch(trueBranch), false_branch(falseBranch) {}
};

class VarAssignNode : public ASTNode {
public:
    Token var_name_token; // Identifier Token
    ASTNode* value;

    json serialize() const override {
        json j;
        j["type"] = "VarAssign";
        j["name"] = var_name_token.value;
        j["node"] = value->getType();
        return j;
    }
    static VarAssignNode* createVariableAssignNode(Token tok, ASTNode* expr) {
        return new VarAssignNode(tok, expr);
    }
    VarAssignNode(Token tok, ASTNode* value) : ASTNode(VAR_ASSIGN_NODE), var_name_token(tok), value(value) {}    
};

class StringNode : public ASTNode {
public:
    std::string value;

    json serialize() const override {
        json j;
        j["type"] = "String";
        j["value"] = value;
        return j;
    }
    StringNode(std::string text) : ASTNode(STRING_NODE), value(text) {}
};

class NumberNode : public ASTNode { // Inherit the ASTNode class
public:
    float value; // The value of the number node.

    NumberNode(float val) : ASTNode(NUMBER_NODE), value(val) {}

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

    int getValue() {
        return value;
    }

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

    UnaryOpNode(Token operator_token, ASTNode* node) : ASTNode(UNARY_OP_NODE), op(operator_token), op_node(node) {}

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

    BinaryOpNode(Token operator_token, ASTNode* leftnode, ASTNode* rightnode) : ASTNode(BINARY_OP_NODE), op(operator_token), left(leftnode), right(rightnode) {}
    
    Token getOperator() {
        return op;
    }

    ASTNode* getLeft() {
        return left;
    }

    ASTNode* getRight() {
        return right;
    }
};
