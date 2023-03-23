#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "defs.h"
#include "BitboardHandler.h"
#include "string"

class ChessPiece {
public:
    ChessPiece(Color color, char character, const std::string &name, const int &value, const PieceIndex &index);

    virtual bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) = 0;

    explicit operator std::string();

    PieceIndex getIndex() const;
    Color getColor() const;
    char getCharacter() const;
    const std::string &getName() const;
    int getValue() const;
private:
    PieceIndex index;
    char character;
    std::string name;
    int value;
protected:
    bitboard boardMask = BitboardHandler::getBoardMask();
    Color color;
};

class Bishop : public ChessPiece {
public:
    explicit Bishop(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
};

class King : public ChessPiece {
public:
    explicit King(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
};

class Knight : public ChessPiece {
public:
    explicit Knight(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
};

class Pawn : public ChessPiece {
public:
    explicit Pawn(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
    int sign;
    bitboard doubleMoveMask;
};

class Queen : public ChessPiece {
public:
    explicit Queen(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
};

class Rook : public ChessPiece {
public:
    explicit Rook(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) override;
private:
};


#endif //CHESS_CHESSPIECE_H
