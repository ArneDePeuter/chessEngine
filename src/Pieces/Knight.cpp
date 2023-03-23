#include "ChessPiece.h"

Knight::Knight(Color color) : ChessPiece(color, 'N', "Knight", 100, knight) {}

bitboard Knight::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    bitboard moves;
    bitboard piecesMask = ~myPieces;

    moves |= BitboardHandler::shift(pieces, FORWARD+FORWARD+LEFT);
    moves |= BitboardHandler::shift(pieces, FORWARD+FORWARD+RIGHT);
    moves |= BitboardHandler::shift(pieces, BACKWARD+BACKWARD+LEFT);
    moves |= BitboardHandler::shift(pieces, BACKWARD+BACKWARD+RIGHT);
    moves |= BitboardHandler::shift(pieces, LEFT+LEFT+FORWARD);
    moves |= BitboardHandler::shift(pieces, LEFT+LEFT+BACKWARD);
    moves |= BitboardHandler::shift(pieces, RIGHT+RIGHT+FORWARD);
    moves |= BitboardHandler::shift(pieces, RIGHT+RIGHT+BACKWARD);

    moves &= piecesMask & boardMask;
    return moves;
}