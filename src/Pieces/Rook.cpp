#include "ChessPiece.h"

Rook::Rook(Color color) : ChessPiece(color, 'R', "Rook", 500, rook) {}

bitboard Rook::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    return 0;
}