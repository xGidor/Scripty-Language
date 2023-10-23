#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <functional>
#include "nodes.hpp"

class NodeVisitor {
public:
    void visit(ASTNode node) {
        std::string nodeType = typeid(*node).name();
        auto visitor = visitors.find(nodeType);
        if (visitor != visitors.end()) {
            visitor->second(node);
        }
        else {
            generic_visit(node);
        }
    }

    void generic_visit(ASTNode node) {
        std::string nodeType = typeid(node).name();
        throw std::runtime_error("No visit_" + nodeType + " method.");
    }
private:
    std::unordered_map<std::string, std::function<void(ASTNode)>> visitors;

public:
    NodeVisitor() {
        // Initialize the visitor map with specific visit functions
        visitors[typeid(IntNode).name()] = [this](ASTNode node) { visit(static_cast<IntNode*>(node)); };
        visitors[typeid(FloatNode).name()] = [this](ASTNode node) { visit(static_cast<FloatNode*>(node)); };
    }