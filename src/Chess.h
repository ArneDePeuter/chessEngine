#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#include "defs.h"
#include "BitboardHandler.h"
#include "Pieces/ChessPiece.h"
#include "string"
#include "Logger.h"
#include "iostream"

class Chess {
public:
    Chess(const std::string &FENstring);
    Chess();
    bool move(const pos &from, const pos &to);
    void print(std::ostream &os) const;
private:
    void setAllMoves(const Color &color);
    void setStartingBoard();
    bitboard *getBitboardAtPos(const pos &p);
    ChessPiece *getPiece(const pos &p) const;
    bitboard getCombinedBoards() const;
    pieceArray piecePointers = {
    std::array<ChessPiece*,6>   {new King(black),new Queen(black),new Rook(black),new Bishop(black),new Knight(black),new Pawn(black)},
                                {new King(white),new Queen(white),new Rook(white),new Bishop(white),new Knight(white),new Pawn(white)}
    };
    bitboardArray bitboards;
    bitboardArray moves;

    std::ostream &errorStream = std::cerr;
};


#endif //CHESS_CHESS_H
