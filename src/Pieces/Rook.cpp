#include "ChessPiece.h"

Rook::Rook(Color color) : SlidingPiece(color, 'R', "Rook", 500, rook) {}

bitboard Rook::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    std::array<int, 8> directions = {
            FORWARD, BACKWARD, LEFT, RIGHT
    };
    return slideToDir(pieces, myPieces, enemyPieces, directions, AnD);
}


