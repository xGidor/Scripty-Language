#include <string>
#include "nodes.hpp"
#include "errors.hpp"

StringNode::StringNode(std::string text)
{
	value = text;
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


