#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

#include "array"

enum Color {black , white};
enum PieceOrder {king, queen, rook, bishop, knight, pawn};

class ChessPiece;
typedef std::array<std::array<ChessPiece*,6>,2> pieceArray;

#endif //CHESS_DEFS_H
