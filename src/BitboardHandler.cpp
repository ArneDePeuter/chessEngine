#include "BitboardHandler.h"

void BitboardHandler::printBitboard(const bitboard &b, std::ostream &os, const bool &chessboard) {
    int rows = (chessboard) ? 8 : 12;
    int cols = (chessboard) ? 8 : 10;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (isOne(b, row, col, chessboard)) {
                os << "1";
            } else {
                os << "0";
            }
        }
        os << std::endl;
    }
    os << std::endl;
}

bool BitboardHandler::isOne(const bitboard &b, const int &row, const int &col, const bool &chessboard) {
    int index = (chessboard) ? (row*10+col)+21 : row*10+col;
    return static_cast<bool>(b & (((bitboard) 1) << index));
}

void BitboardHandler::add(bitboard &b, const int &row, const int &col, const bool &chessboard) {
    int index = (chessboard) ? (row*10+col)+21 : row*10+col;
    b |= ((bitboard) 1) << index;
}

void BitboardHandler::del(bitboard &b, const int &row, const int &col, const bool &chessboard) {
    int index = (chessboard) ? (row*10+col)+21 : row*10+col;
    b &= ~(((bitboard) 1) << index);
}

bitboard BitboardHandler::getBoardMask() {
    return initBoard("631966574893838704558473216000");
}

bitboard BitboardHandler::shift(const bitboard &b, int val) {
    if (val<0) return b >> -val;
    return b << val;
}

bitboard BitboardHandler::initBoard(const std::string &num) {
    return cpp_int(num).convert_to<bitboard>();
}


