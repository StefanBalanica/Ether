#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <list>



class locatie_efect {
public:
    int x;
    int y;
    int tip_efect;

   // locatie_efect();
    locatie_efect(int x, int y, int tip_efect);
};



class Explosion {
private:
    int set_effect();
public:
    Explosion();
    void rotire_matrice_90(std::vector<locatie_efect>& CE);
    std::vector<locatie_efect> generat_carte_explozie_3x3();
    std::vector<locatie_efect> generat_carte_explozie_4x4();
    void afisare_carte_explozie_3x3(std::vector<locatie_efect> CE, int ok, int boardSize);
    void afisare_carte_explozie_4x4(std::vector<locatie_efect> CE, int ok, int boardSize);
};

#endif // EXPLOSION_H
