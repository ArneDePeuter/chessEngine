#include "Chess.h"

int main() {
    bitboard b;
    BitboardHandler::add(b, 4, 4, true);
    ChessPiece *knight = new Knight(black);

    BitboardHandler::printBitboard(b, std::cout, true);
    std::cout << std::endl;
    BitboardHandler::printBitboard(knight->getMoves(b, b, 0), std::cout, true);

    delete knight;
    return 0;
}