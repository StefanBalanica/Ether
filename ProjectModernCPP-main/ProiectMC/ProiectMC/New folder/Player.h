#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <string>

struct Player {
    std::vector<int> cards = { 1, 1, 2, 2, 3, 3, 4, 9 };
    int score = 0;
    std::string color;
    char symbol;
    bool hasUsedMagic = false;
    bool canUseMagic = false;
    bool ceckIluzie = false;
    std::string wizardName = "";
    struct lastPoz {
        int i = -1, j = -1, k = -1;
    }LastPoz;
};

#endif 
