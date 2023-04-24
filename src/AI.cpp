#include "AI.h"
#include "chrono"

AI::AI(Chess *c) : c(c) {}

void AI::perft(std::ostream &os, int depth, const int &initDepth) {
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
    totalPerft = 0;
    perftCounter = 0;
    perft(os, depth, depth);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
}

move AI::getBestMove(int depth) {
    auto start = std::chrono::high_resolution_clock::now();

    simulatedPositions = 0;
    std::pair<double, move> best = minimax(depth, 500000, 500000);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    move bestmove = best.second;
    double eval = best.first;

    std::cout << "Duration: " << duration.count() << " seconds" << std::endl;
    std::cout << "Simulated: " << simulatedPositions << " positions" << std::endl;
    std::cout << "Best move: " << char('a'+bestmove.first.second) << char('8'-bestmove.first.first);
    std::cout << " -> " << char('a'+bestmove.second.second) << char('8'-bestmove.second.first) << std::endl;
    std::cout << "Eval: " << eval << std::endl;
    return bestmove;
}

std::pair<double, move> AI::minimax(int depth, double alpha, double beta) {
    if (depth == 0 || c->gameOver()) {
        if (depth == 0) simulatedPositions++;
        return {c->evaluate(), move (pos(0,0),pos(0,0))};
    }

    Color color = c->getToMove();
    double checkeval = (color == white) ? INT_MIN : INT_MAX;
    move best;
    std::pair<double, move> eval;
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
                        bool moved = c->move(pos(row, col), pos(moveRow, moveCol));
                        if (moved) eval = minimax(depth - 1, alpha, beta);
                        else continue;
                        c->undo();
                        if (color == white) {
                            if (eval.first > checkeval) {
                                checkeval = eval.first;
                                best = move(pos(row, col), pos(moveRow, moveCol));
                            }
                            if (eval.first > alpha) { alpha = eval.first; }
                            if (beta <= alpha) { break; }
                        } else {
                            if (eval.first < checkeval) {
                                checkeval = eval.first;
                                best = move(pos(row, col), pos(moveRow, moveCol));
                            }
                            if (eval.first < beta) { beta = eval.first; }
                            if (beta <= alpha) { break; }
                        }
                    }
                }
            }
        }
    }
    return {checkeval, best};
}


