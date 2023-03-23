#include "ChessPiece.h"

Queen::Queen(Color color) : ChessPiece(color, 'Q', "Queen", 100) {}

bitboard Queen::getMoves(const bitboard &pieces) {
    return 0;
}