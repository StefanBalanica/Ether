#ifndef WIZZARD_H
#define WIZZARD_H

#include "Player.h"
#include <string>
//#include "Game.h"

class Wizzard {
public:
    static void addExtraEther(Player& player);
	static void removeLastOpponentCard(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board);
    static void destroyRow(Player& player, int n1, int n2, int boardSize, std::vector<std::vector<std::vector<int>>>& board);
    static void transformToAbyss(Player& player, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board);
    static void moveStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board);
    static void moveOpponentStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board);
    static void coverOpponentCard(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board);
    static void transportRow(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board);

};
#endif