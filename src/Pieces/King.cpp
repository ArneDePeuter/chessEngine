#include "ChessPiece.h"

King::King(Color color) : ChessPiece(color, 'K', "King", 1000, king) {}

bitboard King::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    bitboard moves;

    moves |= BitboardHandler::shift(pieces, FORWARD);
    moves |= BitboardHandler::shift(pieces, BACKWARD);
    moves |= BitboardHandler::shift(pieces, LEFT);
    moves |= BitboardHandler::shift(pieces, RIGHT);
    moves |= BitboardHandler::shift(pieces, FORWARD+LEFT);
    moves |= BitboardHandler::shift(pieces, FORWARD+RIGHT);
    moves |= BitboardHandler::shift(pieces, BACKWARD+LEFT);
    moves |= BitboardHandler::shift(pieces, BACKWARD+RIGHT);

    if (AnD) return moves & boardMask;

    bitboard piecesMask = ~myPieces;
    moves &= piecesMask & boardMask;
    return moves;
}