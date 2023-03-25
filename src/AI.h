#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "Chess.h"
#include "ostream"

typedef std::pair<pos,pos> move;

class AI {
public:
    explicit AI(Chess *c);
    void perft(std::ostream &os, const int &depth);
    void perft(std::ostream &os, int depth, const int &initDepth);
    std::pair<double,move> minimax(int depth, double alpha, double beta);
    move getBestMove(int depth);
private:
    Chess *c;
    int simulatedPositions = 0;
    int perftCounter = 0;
    int totalPerft = 0;
};


#endif //CHESS_AI_H
