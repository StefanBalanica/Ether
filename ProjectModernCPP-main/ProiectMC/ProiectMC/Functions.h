#pragma once
#include<vector>

#include "Player.h"

class Functions {
public:
  static int lastK(int i, int j, std::vector<std::vector<std::vector<int>>>& board);
  static void translatatePozFor3x3(int& row, int& col, int n1, int n2);
  static void translatatePozFor4x4(int& row, int& col, int n1, int n2);
  static bool checkRow(int boardSize, std::vector<std::vector<std::vector<int>>>& board);
  static bool checkCol(int boardSize, std::vector<std::vector<std::vector<int>>>& board);
  static void returnCard(Player& currentPlayer, Player& opponent, int x, int y, std::vector<std::vector<std::vector<int>>>& board);
  static void removeCard(Player& currentPlayer, Player& opponent, int x, int y, std::vector<std::vector<std::vector<int>>>& board);
  static void printCenteredforBoard(const std::string& text, int ok, int boardSize);
};