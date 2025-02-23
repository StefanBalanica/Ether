#include "Explozie.h"
#include "Player.h"
#include "Game.h";
#include "Functions.h"

using namespace std;
/*
void Explosion::printCenteredforBoard(const std::string& text, int ok, int boardSize)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else {
        consoleWidth = 80;
    }
    int padding;
    if (ok == 1) {
        padding = (consoleWidth - 3) / 2;
    }
    else {
        padding = (consoleWidth - boardSize) / 2;
    }
    if (padding > 0) {
        std::cout << std::string(padding, ' ');
    }
    std::cout << text;
}
*/

Explosion::Explosion() {}

// Constructor definition for locatie_efect
locatie_efect::locatie_efect(int x, int y, int tip_efect) {
    this->x = x;
    this->y = y;
    this->tip_efect = tip_efect;
}


// Definition of set_effect method in Explosion class
int Explosion::set_effect() {
    int numar = rand() % 100 + 1;

    if (numar < 47)
        return 1;
    else if (numar >= 47 && numar < 94)
        return 2;
    else
        return 3;
}

// Definition of rotire_matrice_90 method in Explosion class
void Explosion::rotire_matrice_90(std::vector<locatie_efect>& CE) {
    std::vector<locatie_efect> CE_nou;

    locatie_efect umplutura(0, 0, 0);
    std::vector<std::vector<locatie_efect>> matrix = {
        {umplutura, umplutura, umplutura},
        {umplutura, umplutura, umplutura},
        {umplutura, umplutura, umplutura}
    };

    for (const auto& loc : CE) {
        matrix[loc.x][loc.y].tip_efect = loc.tip_efect;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
        std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (auto& row : matrix) {
        reverse(row.begin(), row.end());
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j].tip_efect > 0) {
                matrix[i][j].x = i;
                matrix[i][j].y = j;
                CE_nou.push_back(matrix[i][j]);
            }
        }
    }

    CE = CE_nou;
}

void Explosion::afisare_carte_explozie_3x3(std::vector<locatie_efect> CE, int ok, int boardSize)
{
   

        locatie_efect umplutura(0, 0, 0);
        std::vector<std::vector<locatie_efect>> matrix = {
            {umplutura, umplutura, umplutura},
            {umplutura, umplutura, umplutura},
            {umplutura, umplutura, umplutura}
        };

        for (const auto& loc : CE) {
            matrix[loc.x][loc.y].tip_efect = loc.tip_efect;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (j == 0) {
                    Functions::printCenteredforBoard(" ", ok, boardSize);
                }
                if (matrix[i][j].tip_efect == 0) {
                    std::cout << "[ ] ";
                }
                else {
                std::cout << "[" << matrix[i][j].tip_efect << "] ";
                }
                
            }
            std::cout << std::endl;
        }
}


// Definition of generat_carte_explozie_3x3 method in Explosion class
std::vector<locatie_efect> Explosion::generat_carte_explozie_3x3() {
    std::vector<locatie_efect> ocupat;
    int numar_efecte = rand() % 3 + 2;

    while (numar_efecte > 0) {
        int x = rand() % 3;
        int y = rand() % 3;

        bool test = true;

        for (const auto& loc : ocupat) {
            if (x == loc.x && y == loc.y) {
                test = false;
                break;
            }
        }

        if (test) {
            int efect = set_effect();
            locatie_efect nou(x, y, efect);
            ocupat.push_back(nou);
            numar_efecte--;
        }
    }

    return ocupat;
}


void Explosion::afisare_carte_explozie_4x4(std::vector<locatie_efect> CE, int ok, int boardSize)
{


    locatie_efect umplutura(0, 0, 0);
    std::vector<std::vector<locatie_efect>> matrix = {
        {umplutura, umplutura, umplutura, umplutura},
        {umplutura, umplutura, umplutura, umplutura},
        {umplutura, umplutura, umplutura, umplutura},
        {umplutura, umplutura, umplutura, umplutura}
    };

    for (const auto& loc : CE) {
        matrix[loc.x][loc.y].tip_efect = loc.tip_efect;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                Functions::printCenteredforBoard(" ", ok, boardSize);
            }
            if (matrix[i][j].tip_efect == 0) {
                std::cout << "[ ] ";
            }
            else {
                std::cout << "[" << matrix[i][j].tip_efect << "] ";
            }

        }
        std::cout << std::endl;
    }
}

std::vector<locatie_efect> Explosion::generat_carte_explozie_4x4() {
    std::vector<locatie_efect> ocupat;
    int numar_efecte = rand() % 4 + 3;

    while (numar_efecte > 0) {
        int x = rand() % 4;
        int y = rand() % 4;

        bool test = true;

        for (const auto& loc : ocupat) {
            if (x == loc.x && y == loc.y) {
                test = false;
                break;
            }
        }

        if (test) {
            int efect = set_effect();
            locatie_efect nou(x, y, efect);
            ocupat.push_back(nou);
            numar_efecte--;
        }
    }

    return ocupat;
}
