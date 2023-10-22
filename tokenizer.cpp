#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.hpp"

// Token Constructor
Token::Token(std::string type_, std::string value_, Position pos_start)
{
    value = value_;
    type = type_;
    if (pos_start.idx != -1) {
        this->pos_start = pos_start.copy();
        this->pos_end = pos_start.copy();
        this->pos_end.advance('\0');
    }

    if (pos_end.idx != -1) {
        this->pos_end = pos_end;
    }
}

// Lexer/Tokenizer Constructor
Lexer::Lexer(std::string fn_, std::string text_)
{
	fn = fn_;
	text = text_;
	position = Position(-1, 0, -1, fn, text);
	current_character = NULL;
	Advance(); // Advance to the 0th character in the text.
}

Position Position::advance(char current_char)
{
	idx++;
	col++;

	if (current_char == '\n') {
		ln++;
		col = 0;
	}

	return *this;
}

// Lexer Advance Function, Advances to the next character in the text.
void Lexer::Advance()
{
	position.advance(current_character);
	current_character = (position.idx < text.length()) ? text[position.idx] : '\0';
}


// Method used to make a number token;
Token Lexer::MakeNumber()
{
	std::string num_str = "";
	int dot_count = 0;

	while (current_character != '\0' && (DIGITS.find(current_character) != std::string::npos || current_character == '.')) { // Check for a valid number character
		if (current_character == '.') { // Check if the number/string has a dot.
			if (dot_count == 1) break;
			dot_count++; //Increase the dot count.
			num_str += '.'; 
		}
		else {
			num_str += current_character; // Add the current character to the number string
		}
		Advance(); // Advance the lexer to the next character.
	}

	if (dot_count == 0) { // IF the number does not have a dot in it return an INT type
		return Token(INT, num_str, position); // Return an INT token type
	}
	else {
		return Token(FLOAT, num_str, position); // Return a FLOAT token type
	}
}


// Default function for making tokens
LexerResult Lexer::MakeTokens()
{
	// Initialize an empty list of tokens
	std::vector<Token> tokens;

	while (current_character != '\0')
	{
		if (current_character == ' ' || current_character == '\t') {
			Advance(); // Advance the lexer;
		} 
		else if (DIGITS.find(current_character) != std::string::npos) {
			tokens.push_back(MakeNumber()); // Add the number token to the tokens list;
		}
		else if (current_character == '+') // Check if the current character of the lexer equals to a specific character.
		{
			tokens.push_back(Token(PLUS, "+", position)); // Add the specified token type to the tokens list, using the integer constructor.
			Advance();
		}
		else if (current_character == '-')
		{
			tokens.push_back(Token(MINUS, "-", position));
			Advance();
		}
		else if (current_character == '*')
		{
			tokens.push_back(Token(MUL, "*", position));
			Advance();
		}
		else if (current_character == '/')
		{
			tokens.push_back(Token(DIV, "/", position));
			Advance(); 
		}
		else if (current_character == '(')
		{
			tokens.push_back(Token(LPAREN, "(", position));
			Advance();
		}
		else if (current_character == ')')
		{
			tokens.push_back(Token(RPAREN, ")", position));
			Advance(); 
		}
		else if (current_character == '{')
		{
			tokens.push_back(Token(LCURLY, "{", position));
			Advance();
		}
		else if (current_character == '}')
		{
			tokens.push_back(Token(RCURLY, "}", position));
			Advance();
		}
		else if (current_character == '^')
		{
			tokens.push_back(Token(POW, "^", position));
			Advance();
		}
		else // If the token is invalid raise error.
		{	
			Position start = position.copy();
			Advance();
			Error err = IllegalCharacterError(start, position, "Got unexpected token at: ");
			LexerResult Result(tokens, err);
			return Result; // return no tokens as we got an error
		}
	};
	tokens.push_back(Token(EOFILE, "\0", position));
	Position start = position.copy();
	NoError NoneError(start,position, "Success.");
	LexerResult Result(tokens, NoneError);
	return Result;
}

