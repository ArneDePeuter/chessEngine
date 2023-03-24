#ifndef CHESS_INTERACTER_H
#define CHESS_INTERACTER_H

#include "Chess.h"
#include "string"
#include "AI.h"

class Interacter {
public:
    Interacter();
    void run();
    bool move();
    void perft();
private:
    Chess game;
    AI *ai;
};


#endif //CHESS_INTERACTER_H
