#include "ChessPiece.h"

King::King(Color color, bool *castleKing, bool *castleQueen) : ChessPiece(color, 'K', "King", 1000, king), castleKing(castleKing), castleQueen(castleQueen) {}

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

    bitboard castleMoves;
    if (color == black && BitboardHandler::isOne(pieces, 0, 4, true)) {
        if (*castleQueen) BitboardHandler::add(castleMoves, 0, 2, true);
        if (*castleKing)  BitboardHandler::add(castleMoves, 0, 6, true);
    } else if (color == black && BitboardHandler::isOne(pieces, 7, 4, true)) {
        if (*castleQueen) BitboardHandler::add(castleMoves, 7, 2, true);
        if (*castleKing)  BitboardHandler::add(castleMoves, 7, 6, true);
    }
    moves |= castleMoves;

    bitboard piecesMask = ~myPieces;
    moves &= piecesMask & boardMask;
    return moves;
}