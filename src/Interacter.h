#ifndef CHESS_INTERACTER_H
#define CHESS_INTERACTER_H

#include "Chess.h"
#include "string"

class Interacter {
public:
    Interacter();
    void run();
    bool move();
private:
    Chess game;
};


#endif //CHESS_INTERACTER_H
