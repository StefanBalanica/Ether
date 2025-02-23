#include <iostream>
#include "Game.h"
#include <thread>
#include <chrono>
#include "Menu.h"  

int main() {
    afiseazaMeniuIntro();  

    int mode = selectGameMode();  

    SetColor(14, 0);  

    int boardSize;
    GameMode currentMode;
    if (mode == 1) {
        std::cout << "Ai ales modul Antrenament.\n";
        currentMode = GameMode::Modul_antrenament;
        boardSize = 5;
    }
    else if (mode == 2) {
        std::cout << "Ai ales modul Duelul_vrajitorilor.\n";
        currentMode = GameMode::Duelul_vrajitorilor;
        boardSize = 7;
    }
    else if (mode == 3) {
        std::cout << "Ai ales modul Duelul_elementelor.\n";
        currentMode = GameMode::Duelul_elementelor;
        boardSize = 7;
    }
    else if (mode == 4) {
        std::cout << "Ai ales modul Duelul_elementelor+Duelul_vrajitorilor.\n";
        currentMode = GameMode::Duelul_elemWizz;
        boardSize = 7;
    }

    SetColor(15, 0);  

    Game game(boardSize, currentMode, "");  
    game.playGame(); 

    return 0;
}
