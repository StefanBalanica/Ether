#ifndef GAME_H
#include "Explozie.h"
#include "Player.h"
#include <vector>
#include <string>
#include <windows.h>
#include "GameModeSettings.h"

class Game {
public:

    void printCentered(const std::string& text, const std::string& alignment);
    void printCenteredforBoard(const std::string& text, int ok);
    std::vector<std::vector<std::vector<int>>> board;
    int totalRounds;
    bool needWizz = false;
    bool needElement = false;
    bool hasUsedMagic = false;
    int hasUsedElements = 0;
    std::string element1;
    std::string element2;
    GameMode Mode;
    Explosion EX;
    std::vector<locatie_efect> CE;
    Player player1, player2;
    Player& currentPlayer = player1;
    Player& opponent = player2;
    bool isPlayer1Turn;
    int boardSize;
    int lastK(int i, int j);
    void iluzie(int i, int j, int cardValue, int turns, Player& currentPlayer, int cardIndex);
    void displayBoard(int n1, int n2, int ok);
    bool checkRow();
    bool checkCol();
    int checkRowForWizz(int n1, int n2, int ok);
    int checkWin(Player& player, int n1, int n2, int turns, int ok);
    bool isAdjacent(int row, int col);
    void addSize(int& n1, int& n2);
    void selectCard(Player& currentPlayer, int& row, int& col, int& cardIndex, int turns, int& cardValue, int ok, int n1, int n2);
    static void translatatePozFor3x3(int& row, int& col, int n1, int n2);
    static void translatatePozFor4x4(int& row, int& col, int n1, int n2);
    void addCardOnBoard(int row, int col, Player& opponent, Player& currentPlayer, int cardValue, int& turns, int cardIndex);
    int addCard(int row, int col, Player& opponent, Player& currentPlayer, int cardValue, int& turns, int cardIndex);
    void  resetGameState(int size);
   

    Game(int size, GameMode currentMode, std::string elem1);
    void playGame();
    void executie_CE( Player& currentPlayer, Player& opponent, std::vector<locatie_efect> CE,int n1, int n2);
    void translatie_CE(std::vector<locatie_efect>& CE, int n1, int n2,int boardsize);
    void returnCard(Player& currentPlayer, Player& opponent, int x, int y);
    void removeCard(Player& currentPlayer, Player& opponent, int x, int y);
};

#endif 

