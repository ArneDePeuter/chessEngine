#ifndef CHESS_BITBOARDHANDLER_H
#define CHESS_BITBOARDHANDLER_H

#include "defs.h"
#include <iostream>

class BitboardHandler {
public:
    static void printBitboard(const bitboard &b, std::ostream &os, const bool &chessboard);
    static bool isOne(const bitboard &b, const int &row, const int &col, const bool &chessboard);
    static void add(bitboard &b, const int &row, const int &col, const bool &chessboard);
    static void del(bitboard &b, const int &row, const int &col, const bool &chessboard);
    static void maskBoard(bitboard &b);
};


#endif //CHESS_BITBOARDHANDLER_H
