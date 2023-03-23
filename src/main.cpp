#include "Chess.h"

int main() {
    Chess c;
    c.print(std::cout);
    c.move(pos(7,0), pos(0,0));
    c.print(std::cout);
    c.move(pos(0,0), pos(7,0));
    c.print(std::cout);
//    c.print(std::cout);
    return 0;
}