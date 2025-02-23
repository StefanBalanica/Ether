
#ifndef ELEMENTE_H
#define ELEMENTE_H

#include "Player.h"
#include <vector>
#include <iostream>

class Elemente {
public:
    static void distrugere(Player& opponent, std::vector<std::vector<std::vector<int>>>& board);
    static void flacari(Player& opponent, Player& currentPlayer,std::vector<std::vector<std::vector<int>>>& board, int boardSize, int ok, int n1, int n2);
    static void lava(Player& opponent, Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize, int n1, int n2);
    static void dinCenusa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void scantei(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void vifor(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void vijelie(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void uragan(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize, bool shiftRight);
    static void rafala(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void miraj(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void furtuna(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void maree(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void ceata(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void val(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void tsunami(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void cascade(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void sprijin(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void cutremur(std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void sfarimare(Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void granite(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void avalansa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void bolovan(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void vartejDeApa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);
    static void ecouEtern(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize);



};
#endif