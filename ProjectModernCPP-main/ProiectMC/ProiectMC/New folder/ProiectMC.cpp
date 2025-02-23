#include <iostream>
#include "Game.h"
int main() {
    int mode;
    std::cout << "Alege modul de joc:\n";
    std::cout << "1. Antrenament\n";
    std::cout << "2. Duel\n";
    std::cout << "Selectie: ";
    std::cin >> mode;

    int boardSize;
    if (mode == 1) {
        std::cout << "Ai ales modul Antrenament.\n";
        boardSize = 5;
    }
    else if (mode == 2) {
        std::cout << "Ai ales modul Duel.\n";
        boardSize = 7;
    }
    else {
        std::cout << "Optiune invalida. Iesire din program.\n";
        return 0;
    }

    Game game(boardSize);
    game.playGame();

    return 0;
}

