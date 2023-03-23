#include "ChessPiece.h"

ChessPiece::ChessPiece(Color color, char character, const std::string &name, const int &value, const PieceIndex &index) : color(color), index(index) {
    ChessPiece::name  = (color==white) ? "White " + name : "Black " + name;
    ChessPiece::value = (color==white) ? value : -value;
    ChessPiece::character = (color==white) ? character : char(tolower(character));
}

Color ChessPiece::getColor() const { return color; }
char ChessPiece::getCharacter() const { return character; }
const std::string &ChessPiece::getName() const { return name; }
int ChessPiece::getValue() const { return value; }

ChessPiece::operator std::string() {
    std::string output;

    output += "Name: " + name + "\n";
    output += "Character: " + std::string(1,character) + "\n";
    output += "Value: " + std::to_string(value) + "\n";

    return output;
}

PieceIndex ChessPiece::getIndex() const {
    return index;
}



