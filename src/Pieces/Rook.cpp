#include "ChessPiece.h"

Rook::Rook(Color color) : ChessPiece(color, 'R', "Rook", 500) {}

bitboard Rook::getMoves(const bitboard &pieces) {
    return 0;
}