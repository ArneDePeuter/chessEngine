#ifndef CHESS_CHESSSTACK_H
#define CHESS_CHESSSTACK_H

#include "defs.h"
#include "stack"

class Chess;

class ChessStack {
public:
    explicit ChessStack(Chess *c);
    void push();
    void pop();
private:
    Chess *c;
    std::stack<castleRightsArray> castleRightsStack;
    std::stack<bitboard> enPassantsStack;
    std::stack<bitboardArray> movesStack;
    std::stack<bitboardArray> bitboardsStack;
    std::stack<bitboard> AnDStack;
};


#endif //CHESS_CHESSSTACK_H
