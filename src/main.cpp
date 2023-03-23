#include "Chess.h"

int main() {
    Chess c;
    c.print(std::cout);
    c.move(pos(0,0), pos(3,0));
    c.print(std::cout);
    return 0;
}