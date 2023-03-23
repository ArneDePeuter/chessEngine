#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#include "defs.h"
#include "BitboardHandler.h"
#include "Pieces/ChessPiece.h"
#include "string"
#include "Logger.h"
#include "iostream"

static bitboard UNUSED = 1;

class Chess {
public:
    Chess(const std::string &FENstring);
    Chess();
    bool move(const pos &from, const pos &to);
    void print(std::ostream &os) const;
    void swap();
    bool gameOver();
private:
    ChessPiece *getPiece(const pos &p, const Color &c) const;
    static Color swapColor(const Color &c);
    ChessPiece *getPiece(const pos &p) const;
    void setStartingBoard();
    bitboard getCombinedBoards(const Color &color) const;
    void setPinLaser();
    void setKingAttackers();
    void setAnD();
    void update();
    bool check() const;
    bool checkmate() const;
    bool stalemate() const;

    pieceArray piecePointers = {
    std::array<ChessPiece*,6>   {new King(black),new Queen(black),new Rook(black),new Bishop(black),new Knight(black),new Pawn(black)},
                                {new King(white),new Queen(white),new Rook(white),new Bishop(white),new Knight(white),new Pawn(white)}
    };
    bitboardArray bitboards;
    bitboardArray moves;
    bitboard AnD;
    bitboard kingAttackers;
    bitboard pinLaser;
    std::ostream &errorStream = std::cerr;
    Color toMove;
};


#endif //CHESS_CHESS_H
