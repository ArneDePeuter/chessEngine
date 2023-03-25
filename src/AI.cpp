#include "AI.h"
#include "chrono"

AI::AI(Chess *c) : c(c) {}

void AI::perft(std::ostream &os, int depth, const int &initDepth) {
    if (depth==initDepth) {
        totalPerft = 0;
    }
    if (depth<=0 || c->gameOver()) {
        perftCounter++;
        totalPerft++;
        return;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = c->getPiece(pos(row, col), c->getToMove());
            if (piece==nullptr) continue;
            bitboard b;
            BitboardHandler::add(b, row, col, true);
            bitboard moves = piece->getMoves(b, c->getCombinedBoards(c->getToMove()), c->getCombinedBoards(c->swapColor(c->getToMove())), false);
            for (int moveRow = 0; moveRow < 8; moveRow++) {
                for (int moveCol = 0; moveCol < 8; moveCol++) {
                    if (BitboardHandler::isOne(moves, moveRow, moveCol, true)) {
                        if (depth==initDepth) {
                            perftCounter = 0;
                            os << char('a'+col) << abs(row-8) << char('a'+moveCol) << abs(moveRow-8) << ": ";
                        }
                        bool moved = c->move(pos(row, col), pos(moveRow, moveCol));
                        if (moved) perft(os, depth-1, initDepth);
                        else continue;
                        c->undo();
                        if (depth==initDepth) {
                            os << perftCounter << std::endl;
                        }
                    }
                }
            }
        }
    }
    if (depth==initDepth) {
        os << "Total positions: " << totalPerft << std::endl;
    }
}

void AI::perft(std::ostream &os, const int &depth) {
    auto start = std::chrono::high_resolution_clock::now();
    perft(os, depth, depth);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
}


