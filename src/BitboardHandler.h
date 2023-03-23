#ifndef CHESS_BITBOARDHANDLER_H
#define CHESS_BITBOARDHANDLER_H

#include <boost/multiprecision/cpp_int.hpp>
#include "iostream"

using namespace boost::multiprecision;

typedef int128_t bitboard;

class BitboardHandler {
public:
    static void printBitboard(const bitboard &b, std::ostream &os, const bool &chessboard);
    static bool isOne(const bitboard &b, const int &row, const int &col, const bool &chessboard);
    static void setOne(bitboard &b, const int &row, const int &col, const bool &chessboard);
};


#endif //CHESS_BITBOARDHANDLER_H
