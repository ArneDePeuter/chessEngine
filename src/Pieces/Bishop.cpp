#include "ChessPiece.h"

Bishop::Bishop(Color color) : SlidingPiece(color, 'B', "Bishop", 50, bishop) {}

bitboard Bishop::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    std::array<int, 8> directions = {
            FORWARD+LEFT, FORWARD+RIGHT, BACKWARD+LEFT, BACKWARD+RIGHT
    };
    return slideToDir(pieces, myPieces, enemyPieces, directions, AnD);
}
