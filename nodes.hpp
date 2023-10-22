#ifndef  NODES_H
#define NODES_H
#include <string>
#include <iostream>
#include <vector>

#include "tokenizer.hpp"

//base Node class
class Node
{
public:
	Token token;
	Node() {}
	Node(Token token);
};

// Node used for dealing with Numbers in the language.
class NumberNode : public Node
{
public:
	NumberNode(Token token);
};

// Node used for binary operations in the language
class BinaryOperationNode : public Node
{
public:
	Node left_node;
	Node right_node;

	BinaryOperationNode(Node left_node, Token token, Node right_node);
};

// Node used for unary operations in the language
class UnaryOperationNode : public Node
{
public:
	Node node;

	UnaryOperationNode(Token token, Node node);
};
#endif