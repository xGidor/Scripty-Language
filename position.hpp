#ifndef  POSITION_H
#define POSITION_H
#include <string>
#include <iostream>
#include <vector>

class Position {
public:
    int idx;    // Index
    int ln;     // Line number
    int col;    // Column number
    std::string fn;  // File name
    std::string ftxt;  // File text

    Position(int index, int line, int column, std::string filename, std::string fileText)
        : idx(index), ln(line), col(column), fn(filename), ftxt(fileText) {}

    // Function to advance the position
    Position advance(char current_char='\0');

    // Default value constructor for Position.
    Position() : idx(-1), ln(0), col(-1), fn(""), ftxt("") {}

    // Function to create a copy of the position
    Position copy() {
        return Position(idx, ln, col, fn, ftxt);
    }
};

#endif