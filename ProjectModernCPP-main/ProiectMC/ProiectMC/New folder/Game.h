#ifndef GAME_H

#include "Player.h"
#include <vector>
#include <string_view>
#include <string>
#include <windows.h>

constexpr std::string_view BLUE = "\033[34m";
constexpr std::string_view RED = "\033[31m";
constexpr std::string_view RESET = "\033[0m";

enum class GameMode {
    Training,
    Duel
};


class Game {
private:

    void printCentered(const std::string& text, const std::string& alignment);
    void printCenteredforBoard(const std::string& text, int ok);
    std::vector<std::vector<std::vector<int>>> board;
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
    void selectCard(Player& currentPlayer, int& row, int& col, int& cardIndex, int turns, int& cardValue);
    void translatatePozFor3x3(int& row, int& col, int n1, int n2);
    void translatatePozFor4x4(int& row, int& col, int n1, int n2);
    void addCardOnBoard(int row, int col, Player& opponent, Player& currentPlayer, int cardValue, int& turns, int cardIndex);
public:
    Game(int size);
    void playGame();
    void addExtraEther(Player& player);
    void removeLastOpponentCard(Player& currentPlayer, Player& opponent);
    void destroyRow(Player& player, int n1, int n2);
    void transformToAbyss(Player& player, int& n1, int& n2, int& ok);
    void moveStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok);
    void moveOpponentStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok);
    void coverOpponentCard(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok);
    void transportRow(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok);




};

#endif 

