#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "tokenizer.hpp"

// Token Constructor
Token::Token(std::string type_, std::string value_, Position pos_start)
{
    value = value_;
    type = type_; 
    if (pos_start.idx != -1) { // Check if the position is vaild
        this->pos_start = pos_start.copy(); // Copy the start position
        this->pos_end = pos_start.copy(); // Copy the start position to the end position
        this->pos_end.advance('\0');
    }

    if (pos_end.idx != -1) { // Check if the position is vaild
        this->pos_end = pos_end;
    }
}


// Lexer/Tokenizer Constructor
Lexer::Lexer() { }

Lexer::Lexer(std::string fn_, std::string text_)
{
	fn = fn_;
	text = text_;
	position = Position(-1, 0, -1, fn, text); // Use the default position for Lexer constructor.
	current_character = '\0'; // Use a null character for the constructor.
	Advance(); // Advance to the 0th character in the text line.
}

// Function used to construct the equals tokens
Token Lexer::MakeEquals()
{
	Token tok_type;
	tok_type.type = EQUALS;
	Position pos_start = position.copy();
	std::string tokstr = "=";
	Advance();
	if (current_character == '=') { // If next character is also equal sign then its an equals equals token.
		Advance();
		tok_type.type = EQUALS_EQUALS;
		tokstr = "==";
	}
	Token tok = Token(tok_type.type, tokstr, pos_start); // Construct our Token class with our equals signs.
	tok.pos_end = position.copy(); // Copy our current position to be the ending position.
	return tok; // Return our token.
}

// Function used to construct the less than tokens
Token Lexer::MakeLessThan()
{
	Token tok_type;
	tok_type.type = LESS_THAN;
	Position pos_start = position.copy();
	std::string tokstr = "<";
	Advance();
	if (current_character == '=')
	{
		Advance();
		tok_type.type = LT_EQUALS;
		tokstr = "<=";
	}
	Token tok = Token(tok_type.type, tokstr, pos_start); // Construct our Token class with our equals signs.
	tok.pos_end = position.copy(); // Copy our current position to be the ending position.
	return tok; // Return our token.	
}

// Function used to construct the greater than tokens.
Token Lexer::MakeGreaterThan()
{
	Token tok_type;
	tok_type.type = GREATER_THAN;
	Position pos_start = position.copy();
	std::string tokstr = ">";
	Advance();
	if (current_character == '=')
	{
		Advance();
		tok_type.type = GT_EQUALS;
		tokstr = ">=";
	}
	Token tok = Token(tok_type.type, tokstr, pos_start); // Construct our Token class with our equals signs.
	tok.pos_end = position.copy(); // Copy our current position to be the ending position.
	return tok; // Return our token.	
}

// Function used to construct the not eqauls token
Token Lexer::MakeNotEquals()
{
	Position pos_start = position.copy();
	Token tok_type;
	Advance();

	if (current_character == '=')
	{
		Advance();
		Token tok = Token(NOT_EQUALS, "!=", pos_start);
		tok.pos_end = position.copy();
		return tok;
	}
	Advance();
	Error err = ExpectedCharacterError(pos_start, position.copy(), ""); // Raise an error as we are not using ! for anything else at the moment
	err.details = "Got unexpected character before '=', was expecting: '!' '<' '>'";
	std::cout << err.as_string();
	exit(false);
}

void Lexer::SkipComments()
{
	Advance();
	while (current_character != '\n')
	{
		if(current_character == '\0')
		{
			return;
		}
		Advance();
	}
	//Advance();
}

// String token constructor
Token Lexer::makeString(char qt) {
	std::string str = ""; // Set string to empty by def.
	Position pos_start = position.copy();
	bool escape_character = false; // No escape character in string by defau�t
	Advance(); // Advance the lexer

	std::map<char, char> escape_characters = {
		{'n', '\n'}, // Newline
		{'t', '\t'}, // Tab
		{'\'', '\''}, // 
		{'"', '\"'} //
	}; // Escape characters

	while (current_character != '\0' && (current_character != qt || escape_character)) {
		if (escape_character) {
			str += escape_characters[current_character];
			escape_character = false;
		}
		else {
			if (current_character == '\\') {
				escape_character = true; // If backslash found then escape characters are in string
				Advance();
				continue;
			}
			else {
				str += current_character; // Add the forbidden character to the string
			}
		}
		Advance();
		escape_character = false; 
	}

	Advance();
	Token tok = Token(STRING, str, pos_start); // Create the string token with our string and start position.
	tok.pos_end = position.copy(); // copy our current position for the ending position.
	return tok; // return the STRING token.
}

// Function to advance the position of the lexer.
Position Position::advance(char current_char)
{
	idx++;
	col++;

	if (current_char == '\n') { // If we encounter a new line set the collumn to 0 and increase the line count.
		ln++; // Increase the line number
		col = 0; // Set the character index to 0 due to a new line
	}

	return *this;
}

// Lexer Advance Function, Advances to the next character in the text.
void Lexer::Advance()
{
	position.advance(current_character); // also advance our position 
	current_character = (position.idx < text.length()) ? text[position.idx] : '\0'; 
}

Token Lexer::MakeIdentifier()
{
	std::string id_str = ""; // make an empty identifier string to use later
	Position pos_start = position.copy();
	while (current_character != '\0' && (LETTERS_DIGITS.find(current_character) != std::string::npos || current_character == '_'))
	{
		id_str += current_character; // add our identifier character to the id string
		Advance();
	}
	std::string type = (KEYWORD.find(id_str) != KEYWORD.end()) ? KEYWORD_ : IDENTIFIER; // check if the identifier string exists as a valid keyword or identifier in the langauge
	Token tok = Token(type, id_str, pos_start);
	return tok;
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
		if (current_character == ' '  || current_character == '\t') {
			Advance(); // Advance the lexer;
		}
		else if (current_character == '#')
		{
			SkipComments();
		}
		else if (current_character == '\n') // automatic handling if its not there (later needs to be revised)
		{
			tokens.push_back(Token(NEW_LINE, ";", position)); 
			Advance();
		}
		else if (current_character == ';')
		{
			tokens.push_back(Token(NEW_LINE, ";", position));
			Advance(); 
			while (current_character == '\n' || current_character == ';')
			{
				Advance(); // Advance another times so we dont add another ; to the token lists due to the \n character after ; if theres any
			}
		}
		else if (current_character == '\'' || current_character == '\"')
		{
			tokens.push_back(makeString(current_character));
		}
		else if (DIGITS.find(current_character) != std::string::npos) {
			tokens.push_back(MakeNumber()); // Add the number token to the tokens list;
		}
		else if (LETTERS.find(current_character) != std::string::npos) {
			tokens.push_back(MakeIdentifier());
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
		else if (current_character == '!')
		{
			tokens.push_back(MakeNotEquals());
		}
		else if (current_character == '=')
		{
			tokens.push_back(MakeEquals());
		}
		else if (current_character == '<')
		{
			tokens.push_back(MakeLessThan());
		}
		else if (current_character == '>')
		{
			tokens.push_back(MakeGreaterThan());
		}
		else if (current_character == '^')
		{
			tokens.push_back(Token(POW, "^", position));
			Advance();
		}
		else if (current_character == ',')
		{
			tokens.push_back(Token(COMMA, ",", position));
			Advance();
		}
		else // If the token is invalid raise error.
		{
			Position start = position.copy();
			Advance();
			Error LexerError = IllegalCharacterError(start, position, "Got unexpected token at: ");
			LexerResult Result(error, LexerError);
			return Result; // return no tokens as we got an error
		}
	};
	tokens.push_back(Token(EOFILE, "\0", position));
	LexerResult Result(tokens, success);
	return Result; // Return the results from the lexer;
}

