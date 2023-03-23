#include "ChessPiece.h"

Queen::Queen(Color color) : SlidingPiece(color, 'Q', "Queen", 100, queen) {}

bitboard Queen::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    std::array<int, 8> directions = {
            FORWARD, BACKWARD, LEFT, RIGHT, FORWARD+LEFT, FORWARD+RIGHT, BACKWARD+LEFT, BACKWARD+RIGHT
    };
    return slideToDir(pieces, myPieces, enemyPieces, directions, AnD);
}