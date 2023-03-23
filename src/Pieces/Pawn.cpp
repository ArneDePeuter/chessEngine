#include "ChessPiece.h"

Pawn::Pawn(Color color, bitboard *enPassant) : ChessPiece(color, 'P', "Pawn", 1, pawn), enPassant(enPassant) {
    sign = (color==black) ? 1 : -1;
    doubleMoveMask = (color==black) ? 560750930165760 : BitboardHandler::initBoard("602101726565879764746240");
}

bitboard Pawn::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    if (AnD) return getAttackMoves(pieces, myPieces, enemyPieces, AnD) & boardMask;

    bitboard moves;

    bitboard piecesMask = myPieces|enemyPieces; //cant move onto any piece

    moves |= BitboardHandler::shift(pieces, sign*FORWARD);
    moves &= ~piecesMask;
    moves |= BitboardHandler::shift(moves&doubleMoveMask, sign*FORWARD);
    moves &= ~piecesMask;

    moves |= getAttackMoves(pieces, myPieces, enemyPieces, AnD);
    moves &= boardMask;
    return moves;
}

bitboard Pawn::getAttackMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces, const bool &AnD) {
    bitboard moves;

    moves |= BitboardHandler::shift(pieces, sign*FORWARD+LEFT);
    moves |= BitboardHandler::shift(pieces, sign*FORWARD+RIGHT);

    if (AnD) {
        return moves & boardMask & enemyPieces;
    }

    return moves & boardMask & (enemyPieces|*enPassant);
}
