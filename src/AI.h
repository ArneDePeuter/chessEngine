#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "Chess.h"
#include "ostream"

class AI {
public:
    explicit AI(Chess *c);
    void perft(std::ostream &os, int depth, const int &initDepth);
private:
    Chess *c;
    int perftCounter = 0;
    int totalPerft = 0;
};


#endif //CHESS_AI_H
