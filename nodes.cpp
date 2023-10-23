#include <string>
#include "nodes.hpp"
#include "errors.hpp"

StringNode::StringNode(std::string text)
{
	value = text;
}


IntNode::IntNode(int number) {
    value = number;
}

// Perform addition with another IntNode
IntNode IntNode::add(const IntNode& other) const {
    return IntNode(value + other.value);
}

// Perform subtraction with another IntNode
IntNode IntNode::subtract(const IntNode& other) const {
    return IntNode(value - other.value);
}

// Perform multiplication with another IntNode
IntNode IntNode::multiply(const IntNode& other) const {
    return IntNode(value * other.value);
}

// Perform division with another IntNode
IntNode IntNode::divide(const IntNode& other) const {
    if (other.value == 0) {
        return IntNode(std::numeric_limits<float>::quiet_NaN());
    }
    return IntNode(value / other.value);
}





FloatNode::FloatNode(float number) {
	value = number;
}

// Perform addition with another NumberNode
FloatNode FloatNode::add(const FloatNode& other) const {
    return FloatNode(value + other.value);
}

// Perform subtraction with another NumberNode
FloatNode FloatNode::subtract(const FloatNode& other) const {
    return FloatNode(value - other.value);
}

// Perform multiplication with another NumberNode
FloatNode FloatNode::multiply(const FloatNode& other) const {
    return FloatNode(value * other.value);
}

// Perform division with another NumberNode
FloatNode FloatNode::divide(const FloatNode& other) const {
    if (other.value == 0) {
        return FloatNode(std::numeric_limits<float>::quiet_NaN());
    }
    return FloatNode(value / other.value);
}

UnaryOpNode::UnaryOpNode(Token operator_token, ASTNode node_)
{
	op = operator_token;
	op_node = node_;
}

BinaryOpNode::BinaryOpNode(Token operator_token, ASTNode leftnode, ASTNode rightnode) {
	op = operator_token;
	left = leftnode;
	right = rightnode;
}