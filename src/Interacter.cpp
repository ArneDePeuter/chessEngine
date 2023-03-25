#include "Interacter.h"

Interacter::Interacter() {
    ai = new AI(&game);
}

void Interacter::run() {
    game.print(std::cout);
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "move"){
            if (move()) {
                game.print(std::cout);
                if (game.gameOver()) {
                    std::cout << "Game over.\n";
                    std::cout << "See ya later!\n";
                    break;
                }
            }
        } else if (input=="undo") {
            game.undo();
            game.print(std::cout);
        } else if (input=="redo") {
            game.redo();
            game.print(std::cout);
        } else if (input == "quit") {
            std::cout << "See ya later!\n";
            break;
        } else if (input == "perft") {
            perft();
        }
    }
}

bool Interacter::move() {
    std::string from;
    std::string to;
    std::cin >> from;
    std::cin >> to;
    int fromRow = (from[1]-'8')*-1;
    int fromCol = from[0]-'a';
    int toRow = (to[1]-'8')*-1;
    int toCol = to[0]-'a';

    return game.move(pos(fromRow, fromCol), pos(toRow, toCol));
}

void Interacter::perft() {
    int depth;
    std::cin >> depth;
    ai->perft(std::cout, depth);
}
