#include "ChessPiece.h"

Pawn::Pawn(Color color) : ChessPiece(color, 'P', "Pawn", 1, pawn) {}

bitboard Pawn::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    return 0;
}