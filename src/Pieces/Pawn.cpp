#include "ChessPiece.h"

Pawn::Pawn(Color color) : ChessPiece(color, 'P', "Pawn", 1, pawn) {
    sign = (color==black) ? 1 : -1;
    doubleMoveMask = (color==black) ? 560750930165760 : BitboardHandler::initBoard("602101726565879764746240");
}

bitboard Pawn::getMoves(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces) {
    bitboard moves;
    bitboard piecesMask = myPieces|enemyPieces; //cant move onto any piece

    moves |= BitboardHandler::shift(pieces, sign*FORWARD);
    moves &= ~piecesMask;
    moves |= BitboardHandler::shift(moves&doubleMoveMask, sign*FORWARD);
    moves &= ~piecesMask;

    moves &= boardMask;
    return moves;
}