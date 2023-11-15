
#ifndef TOKENS_H
#define TOKENS_H
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "../position/position.hpp"

//Define the Token struct
class Token
{
public:
	std::string type;
	std::string value;
	Position pos_start;
	Position pos_end;
	Token() {} // Add a default constructor so Token can be used with Node classes
	Token(std::string type_, std::string value_, Position pos_start); 

	friend std::ostream& operator<<(std::ostream& os, const Token& token) {
		os << "Token { Type: " << token.type << ", Value: '" << token.value << "' }";
		return os;
	}
};

#endif