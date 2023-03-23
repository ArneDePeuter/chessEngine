#include "ChessPiece.h"

Knight::Knight(Color color) : ChessPiece(color, 'N', "Knight", 100, knight) {}

bitboard Knight::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    return 0;
}