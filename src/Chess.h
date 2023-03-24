#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#include "defs.h"
#include "BitboardHandler.h"
#include "Pieces/ChessPiece.h"
#include "string"
#include "Logger.h"
#include "iostream"

class ChessStack;

class Chess {
public:
    Chess(const std::string &FENstring);
    Chess();
    bool move(const pos &from, const pos &to);
    void print(std::ostream &os) const;
    void swap();
    bool gameOver();
    void undo();
    void redo();
    const bitboard &getEnPassant() const;
    const castleRightsArray &getCastleRights() const;
    const bitboardArray &getBitboards() const;
    const bitboardArray &getMoves() const;
    const bitboard &getAnD() const;
    void setEnPassant(const bitboard &enPassant);
    void setCastleRights(const castleRightsArray &castleRights);
    void setBitboards(const bitboardArray &bitboards);
    void setMoves(const bitboardArray &moves);
    void setAnD(const bitboard &anD);
    ChessPiece *getPiece(const pos &p, const Color &c) const;
    ChessPiece *getPiece(const pos &p) const;
    Color getToMove() const;
    bitboard getCombinedBoards(const Color &color) const;
    static Color swapColor(const Color &c);
private:
    void setStartingBoard();
    void setPinLaser();
    void setKingAttackers();
    void setAnD();
    void update();
    bool check() const;
    bool checkmate() const;
    bool stalemate() const;
    void handleEnpassant(ChessPiece *movedPiece, const pos &from, const pos &to);
    bool validCastle(ChessPiece *movedPiece, const pos &from, const pos &to);

    bitboard enPassant;
    castleRightsArray castleRights;
    pieceArray piecePointers = {
    std::array<ChessPiece*,6>   {new King(black, &castleRights[bCastleK], &castleRights[bCastleQ]),new Queen(black),new Rook(black),new Bishop(black),new Knight(black),new Pawn(black, &enPassant)},
                                {new King(white, &castleRights[wCastleK], &castleRights[wCastleQ]),new Queen(white),new Rook(white),new Bishop(white),new Knight(white),new Pawn(white, &enPassant)}
    };
    bitboardArray bitboards;
    bitboardArray moves;
    bitboard AnD;
    bitboard kingAttackers;
    bitboard pinLaser;
    std::ostream &errorStream = std::cerr;
    Color toMove;

    ChessStack *undostack;
    ChessStack *redostack;
};


#endif //CHESS_CHESS_H
