#include "ChessPiece.h"

SlidingPiece::SlidingPiece(Color color, char character, const std::string &name, const int &value,
                           const PieceIndex &index) : ChessPiece(color, character, name, value, index) {}


bitboard SlidingPiece::slideToDir(const bitboard &pieces, const bitboard &myPieces, const bitboard &enemyPieces,
                                  const std::array<int, 8> &directions, const bool &AnD) {
    bitboard moves;
    for (int direction : directions) {
        bitboard moveSet = pieces;
        bitboard piecesMask = boardMask;
        piecesMask &= (AnD) ? ~BitboardHandler::shift(myPieces, direction) : ~myPieces;
        piecesMask &= ~BitboardHandler::shift(enemyPieces, direction);

        bool updating = true;
        bool firstEnter = true;
        bitboard prev;
        while (updating) {
            prev = moveSet;
            moveSet |= BitboardHandler::shift(moveSet, direction);
            moveSet &= piecesMask;

            updating = prev!=moveSet;

            if (firstEnter) {
                moveSet &= ~pieces;
                firstEnter = false;
            }
        }
        moves |= moveSet;
    }
    moves &= boardMask;
    return moves;
}