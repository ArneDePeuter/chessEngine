#include "ChessPiece.h"

Pawn::Pawn(Color color) : ChessPiece(color, 'P', "Pawn", 1) {}

bitboard Pawn::getMoves(const bitboard &pieces) {
    return 0;
}