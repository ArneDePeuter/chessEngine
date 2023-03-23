#include "ChessPiece.h"

SlidingPiece::SlidingPiece(Color color, char character, const std::string &name, const int &value,
                           const PieceIndex &index) : ChessPiece(color, character, name, value, index) {}


bitboard SlidingPiece::slideToDir(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces,
                                  const std::array<int, 8> &directions, const bool &AnD) {
    bitboard moves;
    for (int direction : directions) {
        bitboard moveSet = pieces;
        bitboard piecesMask = boardMask;
        piecesMask &= (AnD) ? ~BitboardHandler::shift(myPieces&~pieces, direction) : ~myPieces;
        piecesMask &= ~BitboardHandler::shift(enemyPieces, direction);

        bool updating = true;
        int i = 0;
        bitboard prev;
        while (updating) {
            prev = moveSet;
            moveSet |= BitboardHandler::shift(moveSet, direction);
            moveSet &= piecesMask;
            updating = prev!=moveSet;

            if (i==0) {
                moveSet &= ~pieces;
            } else if (i==1&&AnD) {
                piecesMask &= ~BitboardHandler::shift(pieces, direction);
            }
            moves |= moveSet;
            i++;
        }
    }
    moves &= boardMask;
    return moves;
}