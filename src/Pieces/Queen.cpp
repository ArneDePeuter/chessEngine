#include "ChessPiece.h"

Queen::Queen(Color color) : ChessPiece(color, 'Q', "Queen", 100, queen) {}

bitboard Queen::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    return 0;
}