#include "ChessPiece.h"

Knight::Knight(Color color) : ChessPiece(color, 'N', "Knight", 100) {}

bitboard Knight::getMoves(const bitboard &pieces) {
    return 0;
}