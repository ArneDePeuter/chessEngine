#include "Chess.h"

int main() {
    Chess c;
    c.print(std::cout);
    std::cout << std::endl;
    c.move(pos(1,0), pos(3,0));
    c.print(std::cout);
    return 0;
}