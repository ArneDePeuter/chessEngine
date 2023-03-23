#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "defs.h"
#include "BitboardHandler.h"
#include "string"

class ChessPiece {
public:
    ChessPiece(Color color, char character, const std::string &name, const int &value, const PieceIndex &index);

    virtual bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) = 0;

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

class King : public ChessPiece {
public:
    explicit King(Color color, bool *castleKing, bool *castleQueen);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
private:
    bool *castleKing;
    bool *castleQueen;
};

class Knight : public ChessPiece {
public:
    explicit Knight(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
};

class Pawn : public ChessPiece {
public:
    explicit Pawn(Color color, bitboard *enPassant);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
private:
    bitboard getAttackMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD);
    int sign;
    bitboard *enPassant;
    bitboard doubleMoveMask;
};

class SlidingPiece : public ChessPiece {
public:
    SlidingPiece(Color color, char character, const std::string &name, const int &value, const PieceIndex &index);
    bitboard slideToDir(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const std::array<int, 8> &directions, const bool &AnD);
};

class Queen : public SlidingPiece {
public:
    explicit Queen(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
};

class Rook : public SlidingPiece {
public:
    explicit Rook(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
};

class Bishop : public SlidingPiece {
public:
    explicit Bishop(Color color);
    bitboard getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) override;
};


#endif //CHESS_CHESSPIECE_H
