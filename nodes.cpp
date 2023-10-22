#include <string>
#include "nodes.hpp"
#include "errors.hpp"

StringNode::StringNode(std::string text)
{
	value = text;
}

NumberNode::NumberNode(float number) {
	value = number;
}

// Perform addition with another NumberNode
NumberNode NumberNode::add(const NumberNode& other) const {
    return NumberNode(value + other.value);
}

// Perform subtraction with another NumberNode
NumberNode NumberNode::subtract(const NumberNode& other) const {
    return NumberNode(value - other.value);
}

// Perform multiplication with another NumberNode
NumberNode NumberNode::multiply(const NumberNode& other) const {
    return NumberNode(value * other.value);
}

// Perform division with another NumberNode
NumberNode NumberNode::divide(const NumberNode& other) const {
    if (other.value == 0) {
        return NumberNode(std::numeric_limits<float>::quiet_NaN());
    }
    return NumberNode(value / other.value);
}

UnaryOpNode::UnaryOpNode(Token operator_token, ASTNode* node_)
{
	op = operator_token;
	op_node = node_;
}

BinaryOpNode::BinaryOpNode(Token operator_token, ASTNode* leftnode, ASTNode* rightnode) {
	op = operator_token;
	left = leftnode;
	right = rightnode;
}