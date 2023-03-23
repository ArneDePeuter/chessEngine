#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "defs.h"
#include "string"

class ChessPiece {
public:
    ChessPiece(Color color, char character, const std::string &name, const int &value);

    explicit operator std::string();

    Color getColor() const;
    char getCharacter() const;
    const std::string &getName() const;
    int getValue() const;
private:
    Color color;
    char character;
    std::string name;
    int value;
};


#endif //CHESS_CHESSPIECE_H
