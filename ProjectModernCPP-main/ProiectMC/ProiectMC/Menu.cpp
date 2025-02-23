#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include "Menu.h"  

void SetColor(int textColor, int backgroundColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backgroundColor << 4) | textColor);
}

void setConsoleCursorPosition(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearConsole() {
    system("cls");
}

int selectGameMode() {
    clearConsole();

    SetColor(14, 0);
    setConsoleCursorPosition(0, 0); 
    std::cout << "Alege modul de joc:\n";
    std::cout << "\n";  

    
    SetColor(14, 0);
    setConsoleCursorPosition(0, 2);
    std::cout << "1. Modul_antrenamet\n";
    setConsoleCursorPosition(0, 3);
    std::cout << "2. Duelul_vrajitorilor\n";
    setConsoleCursorPosition(0, 4);
    std::cout << "3. Duelul_elementelor\n";
    setConsoleCursorPosition(0, 5);
    std::cout << "4. Duelul_elementelor+Duelul_vrajitorilor\n";
    setConsoleCursorPosition(0, 7);
    std::cout << "Selectie: ";
    int mode;
    std::cin >> mode;
    std::cout << "\n";

    SetColor(15, 0);  

    return mode;
}

void afiseazaMeniuIntro() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.dwSize.X;
    int consoleHeight = csbi.dwSize.Y;

    int centerX = consoleWidth / 2;
    int centerY = consoleHeight / 3;

    COORD coord = { centerX - 10, centerY };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    SetColor(9, 0);
    std::string text = "Bine ai venit pe jocul ";
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    SetColor(12, 0);
    text = "Eter";
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }

    SetColor(9, 0);
    std::cout << " ";

    SetColor(9, 0);
    std::cout << "!";

    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    SetColor(9, 0);
    text = "pentru a continua apasa Enter";
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    SetColor(9, 0);
    text = " ...";
    for (char c : text) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    coord.Y = consoleHeight - 2;
    coord.X = (consoleWidth / 2) - 30;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    SetColor(13, 0);
    text = "Balanica Stefan | Bangala Costin | Balca Eduard | Chalapco Madalin";
    std::cout << text;

    SetColor(15, 0);  

    std::cin.ignore();
    std::cin.get();
}
