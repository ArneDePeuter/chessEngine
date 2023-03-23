#include "ChessPiece.h"

King::King(Color color) : ChessPiece(color, 'K', "King", 1000, king) {}

bitboard King::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    return 0;
}