#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
struct Player {
    std::vector<int> cards;
    int score = 0;
    int totalscore = 0;
    std::string color;
    char symbol;
    bool hasUsedMagic = false;
    bool ceckIluzie = false;
    std::string wizardName = "";
    struct lastPoz {
        int i = -1, j = -1, k = -1;
    } LastPoz;

    int restrictedRow = -1;  
};

#endif
