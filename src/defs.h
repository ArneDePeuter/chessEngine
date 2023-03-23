#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

#include <array>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

typedef int128_t bitboard;
typedef std::array<std::array<bitboard,6>,2> bitboardArray;

enum Color {black , white};
enum PieceOrder {king, queen, rook, bishop, knight, pawn};

class ChessPiece;

typedef std::array<std::array<ChessPiece*,6>,2> pieceArray;

typedef std::pair<int,int> pos;

#endif //CHESS_DEFS_H
