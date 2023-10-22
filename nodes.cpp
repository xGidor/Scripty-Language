#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "nodes.hpp"

Node::Node(Token Token)
{
	token = Token;
}

NumberNode::NumberNode(Token Token)
{
	token = Token;
}

UnaryOperationNode::UnaryOperationNode(Token Token, Node Node)
{
	token = Token;
	node = Node;
}

BinaryOperationNode::BinaryOperationNode(Node leftNode, Token Token, Node rigthNode)
{
	left_node = leftNode;
	token = Token;
	right_node = rigthNode;
}