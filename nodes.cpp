#include <string>
#include "nodes.hpp"

StringNode::StringNode(std::string text)
{
	value = text;
}

NumberNode::NumberNode(float number) {
	value = number;
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