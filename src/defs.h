#ifndef CHESS_DEFS_H
#define CHESS_DEFS_H

#include <array>
#include <boost/multiprecision/cpp_int.hpp>

const int FORWARD = 10;
const int LEFT = 1;
const int BACKWARD = -FORWARD;
const int RIGHT = -LEFT;

using namespace boost::multiprecision;

typedef uint128_t bitboard;
typedef std::array<std::array<bitboard,6>,2> bitboardArray;
typedef std::array<bool,4> castleRightsArray;

enum Color {black , white};
enum PieceIndex {king, queen, rook, bishop, knight, pawn};
enum castleIndex {wCastleQ, wCastleK, bCastleQ, bCastleK};

class ChessPiece;

typedef std::array<std::array<ChessPiece*,6>,2> pieceArray;

typedef std::pair<int,int> pos;

#endif //CHESS_DEFS_H
