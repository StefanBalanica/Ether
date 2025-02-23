#include "Elemente.h"
#include "Functions.h"
#include "Game.h"
void Elemente::distrugere(Player& opponent, std::vector<std::vector<std::vector<int>>>& board)
{
    if (opponent.LastPoz.i == -1 || opponent.LastPoz.j == -1) {
        std::cout << "Nu există nicio carte a adversarului de eliminat!\n";
        return;
    }

    int i = opponent.LastPoz.i;
    int j = opponent.LastPoz.j;
    int k = opponent.LastPoz.k;

    opponent.score -= abs(board[i][j][k]);
    board[i][j][k] = 0;

    std::cout << "Ultima carte a adversarului a fost eliminată de pe poziția ("
        << i << ", " << j << ").\n";
    opponent.LastPoz = { -1, -1, -1 };
}

void Elemente::flacari(Player& opponent, Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize, int ok, int n1, int n2)
{
    int i;
    int value;
    if (currentPlayer.symbol == 'A') {
        value = -11;
    }
    else {
        value = 11;
    }
    for ((ok == 1 ? i = n1 : i = 0); (ok == 1 ? i < n1 + 4 : i < boardSize); i++) {
        for (int j = n2 - 3; j <= n2; j++) {
    if (board[i][j][Functions::lastK(i, j, board)] == value) {
        board[i][j][Functions::lastK(i, j, board)] = 0;
        std::cout << "Iluzia de pe poziția (" << i << ", " << j << ") a fost întoarsă cu fața în sus.\n";
    }
        }
    }
}

void Elemente::lava(Player& opponent, Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize,  int n1, int n2)
{
    int input;

    std::cout << "Alege un numar intre 1 si 4" << std::endl;

    std::cin >> input;

    int ok = 0;

    while (input < 1 || input>4)
    {
        std::cout << "Input gresit, incearca din nou";
        std::cin >> input;
    }
   
    int count = 0;

    while (ok)
    {
        for (int i = n1; i <= n1 + 3; i++)
            for (int j = n2 - 3; j <= n2; i++)
            {
                if (board[i][j][Functions::lastK(i,j,board)] == input)
                    count++;
            }

        if (count < 2)
        {
            std::cout << "Nu sunt cel putin 2 carti cu acel numar vizibile pe tabla" << std::endl;
            count = 0;
        }
        else
            ok = 1;

    }

    for (int i = n1; i <= n1 + 3; i++)
        for (int j = n2 - 3; j <= n2; i++)
        {
            if (board[i][j][Functions::lastK(i, j, board)] == input)
            {

                Functions::returnCard(opponent, currentPlayer, i, j, board);

            }
        }

}

void Elemente::dinCenusa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    
    if (currentPlayer.cards.empty())
    {
        std::cout << "Nu ai nici o carte eliminata din joc.\n";
        return;
    }

    std::cout << "Alege o carte eliminata:\n";
    for (size_t i = 0; i < currentPlayer.cards.size(); ++i)
    {
        std::cout << i + 1 << ". " << currentPlayer.cards[i] << "\n";
    }

    int cardIndex;
    std::cout << "Introdu numarul cărții pe care vrei să o joci: ";
    std::cin >> cardIndex;

    if (cardIndex < 1 || cardIndex > currentPlayer.cards.size())
    {
        std::cout << "Alegere invalida!\n";
        return;
    }

    int chosenCard = currentPlayer.cards[cardIndex - 1];

    bool placed = false;
    for (int i = 0; i < boardSize && !placed; ++i)
    {
        for (int j = 0; j < boardSize && !placed; ++j)
        {
            for (int k = 0; k < boardSize && !placed; ++k)
            {
                if (board[i][j][k] == 0)  
                {
                    board[i][j][k] = chosenCard; 
                    currentPlayer.cards.erase(currentPlayer.cards.begin() + (cardIndex - 1));  
                    placed = true;
                    std::cout << "Cartea cu valoarea " << chosenCard << " a fost jucata pe pozitia (" << i << ", " << j << ").\n";
                }
            }
        }
    }

    if (!placed)
    {
        std::cout << "Nu am gasit o pozitie disponibila pe tabla.\n";
    }
}

void Elemente::scantei(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    std::vector<std::tuple<int, int, int>> coveredCards;

    for (int x = 0; x < boardSize; ++x) {
        for (int y = 0; y < boardSize; ++y) {
            for (int z = 0; z < boardSize; ++z) {
                if (board[x][y][z] < 0) {
                    coveredCards.emplace_back(x, y, z);
                }
            }
        }
    }

    if (coveredCards.empty()) {
        std::cout << "Nu ai nicio carte acoperită de adversar!\n";
        return;
    }

    std::cout << "Alege o carte acoperită de adversar pe care vrei să o joci:\n";
    for (size_t index = 0; index < coveredCards.size(); ++index) {
        auto [x, y, z] = coveredCards[index];
        std::cout << index + 1 << ". Pozitia (" << x << ", " << y << ") cu valoarea " << abs(board[x][y][z]) << "\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(coveredCards.size())) {
        std::cout << "Selectie invalida.\n";
        return;
    }

    auto [x, y, z] = coveredCards[choice - 1];
    int cardValue = abs(board[x][y][z]);

    int newX, newY;
    std::cout << "Alege o noua pozitie pentru cartea ta (x y): ";
    std::cin >> newX >> newY;

    if (newX < 0 || newX >= boardSize || newY < 0 || newY >= boardSize || board[newX][newY][Functions::lastK(newX, newY, board)] != 0) {
        std::cout << "Pozitia aleasa este invalida.\n";
        return;
    }

    board[x][y][z] = 0;
    board[newX][newY][Functions::lastK(newX, newY, board)] = cardValue;

    std::cout << "Cartea a fost jucată pe poziția (" << newX << ", " << newY << ").\n";
}

void Elemente::vifor(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    std::vector<std::pair<int, int>> visibleCards;

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            for (int k = 0; k < boardSize; ++k)
            {
                if (board[i][j][k] > 0 && board[i][j][k] != 0) 
                {
                    visibleCards.push_back({ i, j });
                }
            }
        }
    }

    if (visibleCards.empty())
    {
        std::cout << "Nu sunt carti vizibile ale oponentului!\n";
        return;
    }

    std::cout << "Alege o carte vizibila a oponentului pe care vrei sa o intoarci in mana ta:\n";
    for (size_t index = 0; index < visibleCards.size(); ++index)
    {
        int i = visibleCards[index].first;
        int j = visibleCards[index].second;
        int k = Functions::lastK(i, j, board);
        std::cout << "Pozitia (" << i << ", " << j << ") cu valoarea " << board[i][j][k] << std::endl;
    }

    int choice;
    std::cout << "Alege pozitia (1-" << visibleCards.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > visibleCards.size())
    {
        std::cout << "Selectie invalida.\n";
        return;
    }

    int i = visibleCards[choice - 1].first;
    int j = visibleCards[choice - 1].second;
    int k = Functions::lastK(i, j, board);
    int cardValue = board[i][j][k];

    opponent.score -= abs(cardValue); 
    opponent.cards.erase(std::remove(opponent.cards.begin(), opponent.cards.end(), abs(cardValue)), opponent.cards.end()); 
    currentPlayer.score += abs(cardValue); 
    currentPlayer.cards.push_back(abs(cardValue)); 
    board[i][j][k] = 0; 

    std::cout << "Cartea " << cardValue << " a fost intorcuta in mana ta.\n";
}

void Elemente::vijelie(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    std::vector<std::tuple<int, int, int>> coveredCards; 

    
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            for (int k = 0; k < boardSize; ++k) {
                if (board[i][j][k] < 0) { 
                    coveredCards.push_back({ i, j, k });
                }
            }
        }
    }

    if (coveredCards.empty()) {
        std::cout << "Nu sunt cărți acoperite de alte cărți pe tabla de joc.\n";
        return;
    }

    std::cout << "Toate cărțile acoperite se întorc în mâinile proprietarilor:\n";

    
    for (const auto& [i, j, k] : coveredCards) {
        int cardValue = abs(board[i][j][k]); 

        if (cardValue > 0) {
            currentPlayer.score += cardValue;
            currentPlayer.cards.push_back(cardValue);
            std::cout << "Cartea cu valoarea " << cardValue << " de la poziția (" << i << ", " << j << ") s-a întors în mâna ta.\n";
        }
        else {
            opponent.score += cardValue;
            opponent.cards.push_back(cardValue);
            std::cout << "Cartea cu valoarea " << cardValue << " de la poziția (" << i << ", " << j << ") s-a întors în mâna adversarului.\n";
        }

        board[i][j][k] = 0; 
    }
}


void Elemente::uragan(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize, bool shiftRight)
{
    int direction = shiftRight ? 1 : -1;
    bool cardMoved = false;

    for (int i = 0; i < boardSize; ++i)
    {
        std::vector<int> rowValues;
        for (int j = 0; j < boardSize; ++j)
        {
            rowValues.push_back(board[i][j][Functions::lastK(i, j, board)]);
        }

        if (shiftRight)
        {
            rowValues.insert(rowValues.begin(), rowValues.back());
            rowValues.pop_back();
        }
        else
        {
            rowValues.push_back(rowValues.front());
            rowValues.erase(rowValues.begin());
        }

        for (int j = 0; j < boardSize; ++j)
        {
            int cardValue = rowValues[j];
            if (cardValue != 0)
            {
                int k = Functions::lastK(i, j, board);
                if (cardValue < 0)
                {
                    opponent.score -= abs(cardValue);
                    opponent.cards.push_back(abs(cardValue));
                }
                else
                {
                    currentPlayer.score -= abs(cardValue);
                    currentPlayer.cards.push_back(abs(cardValue));
                }
                board[i][j][k] = 0;
            }
            board[i][j][Functions::lastK(i, j, board)] = rowValues[j];
        }
    }
}

void Elemente::rafala(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    std::vector<std::pair<int, int>> visibleCards;

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            for (int k = 0; k < boardSize; ++k)
            {
                if (board[i][j][k] != 0)
                {
                    visibleCards.push_back({ i, j });
                }
            }
        }
    }

    if (visibleCards.empty())
    {
        std::cout << "Nu sunt carti vizibile pe tabla!\n";
        return;
    }

    std::cout << "Alege o carte vizibila pe care vrei sa o muti:\n";
    for (size_t index = 0; index < visibleCards.size(); ++index)
    {
        int i = visibleCards[index].first;
        int j = visibleCards[index].second;
        int k = Functions::lastK(i, j, board);
        std::cout << "Pozitia (" << i << ", " << j << ") cu valoarea " << board[i][j][k] << std::endl;
    }

    int choice;
    std::cout << "Alege pozitia (1-" << visibleCards.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > visibleCards.size())
    {
        std::cout << "Selectie invalida.\n";
        return;
    }

    int i = visibleCards[choice - 1].first;
    int j = visibleCards[choice - 1].second;
    int k = Functions::lastK(i, j, board);
    int cardValue = board[i][j][k];

    std::cout << "Alege directia de mutare (1 - orizontal, 2 - vertical): ";
    int direction;
    std::cin >> direction;

    if (direction == 1)
    {
        if (j > 0 && board[i][j - 1][k] < cardValue)
        {
            board[i][j - 1][k] = cardValue;
            board[i][j][k] = 0;
            std::cout << "Cartea a fost mutata pe pozitia (" << i << ", " << j - 1 << ").\n";
        }
        else if (j < boardSize - 1 && board[i][j + 1][k] < cardValue)
        {
            board[i][j + 1][k] = cardValue;
            board[i][j][k] = 0;
            std::cout << "Cartea a fost mutata pe pozitia (" << i << ", " << j + 1 << ").\n";
        }
        else
        {
            std::cout << "Nu exista o carte mai mica pe o pozitie adiacenta.\n";
        }
    }
    else if (direction == 2)
    {
        if (i > 0 && board[i - 1][j][k] < cardValue)
        {
            board[i - 1][j][k] = cardValue;
            board[i][j][k] = 0;
            std::cout << "Cartea a fost mutata pe pozitia (" << i - 1 << ", " << j << ").\n";
        }
        else if (i < boardSize - 1 && board[i + 1][j][k] < cardValue)
        {
            board[i + 1][j][k] = cardValue;
            board[i][j][k] = 0;
            std::cout << "Cartea a fost mutata pe pozitia (" << i + 1 << ", " << j << ").\n";
        }
        else
        {
            std::cout << "Nu exista o carte mai mica pe o pozitie adiacenta.\n";
        }
    }
    else
    {
        std::cout << "Directie invalida.\n";
    }
}

void Elemente::miraj(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    if (!currentPlayer.ceckIluzie) {
        std::cout << "Nu ai nicio iluzie plasată pe tablă pentru a o înlocui.\n";
        return;
    }

    std::vector<std::pair<int, int>> freePositions;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j][0] == 0) {
                freePositions.emplace_back(i, j);
            }
        }
    }

    if (freePositions.empty()) {
        std::cout << "Nu sunt poziții libere pe tablă pentru a înlocui iluzia.\n";
        return;
    }

    std::cout << "Alege o poziție liberă pentru a înlocui iluzia:\n";
    for (size_t index = 0; index < freePositions.size(); ++index) {
        auto [i, j] = freePositions[index];
        std::cout << index + 1 << ". Pozitia (" << i << ", " << j << ")\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(freePositions.size())) {
        std::cout << "Selecție invalidă.\n";
        return;
    }

    auto [i, j] = freePositions[choice - 1];
    board[i][j][0] = currentPlayer.symbol == 'A' ? -1 : 1;
    currentPlayer.ceckIluzie = false;

    std::cout << "Iluzia a fost înlocuită pe poziția (" << i << ", " << j << ").\n";
}


void Elemente::furtuna(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    std::cout << "Alege un teanc de carti pe care vrei sa-l elimini (teancuri cu 2 sau mai multe carti):\n";

    
    std::vector<std::pair<int, int>> validStacks;
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            int cardCount = 0;
            for (int k = 0; k < boardSize; ++k)
            {
                if (board[i][j][k] != 0)
                {
                    ++cardCount;
                }
            }

            if (cardCount >= 2)
            {
                validStacks.push_back({ i, j });
            }
        }
    }

    
    if (validStacks.empty())
    {
        std::cout << "Nu exista teancuri cu 2 sau mai multe carti.\n";
        return;
    }

    
    std::cout << "Teancuri disponibile:\n";
    for (size_t index = 0; index < validStacks.size(); ++index)
    {
        int i = validStacks[index].first;
        int j = validStacks[index].second;
        std::cout << index + 1 << ". Teancul de la pozitia (" << i << ", " << j << ")\n";
    }

    
    int choice;
    std::cout << "Alege pozitia teancului (1-" << validStacks.size() << "): ";
    std::cin >> choice;

    
    if (choice < 1 || choice > static_cast<int>(validStacks.size()))
    {
        std::cout << "Selectie invalida.\n";
        return;
    }

   
    int i = validStacks[choice - 1].first;
    int j = validStacks[choice - 1].second;

    for (int k = 0; k < boardSize; ++k)
    {
        board[i][j][k] = 0; 
    }

    std::cout << "Teancul de carti de la pozitia (" << i << ", " << j << ") a fost eliminat din joc.\n";
}

void Elemente::maree(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    std::vector<std::pair<int, int>> validStacks;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (Functions::lastK(i, j, board) >= 0) {
                validStacks.emplace_back(i, j);
            }
        }
    }

    if (validStacks.size() < 2) {
        std::cout << "Nu există suficiente teancuri pentru a face interschimbul.\n";
        return;
    }

    std::cout << "Teancuri disponibile:\n";
    for (size_t index = 0; index < validStacks.size(); ++index) {
        auto [i, j] = validStacks[index];
        std::cout << index + 1 << ". Teancul de la poziția (" << i << ", " << j << ")\n";
    }

    int choice1, choice2;
    std::cout << "Alege primul teanc (1-" << validStacks.size() << "): ";
    std::cin >> choice1;
    std::cout << "Alege al doilea teanc (1-" << validStacks.size() << "): ";
    std::cin >> choice2;

    if (choice1 < 1 || choice1 > static_cast<int>(validStacks.size()) ||
        choice2 < 1 || choice2 > static_cast<int>(validStacks.size()) || choice1 == choice2) {
        std::cout << "Selecție invalidă.\n";
        return;
    }

    auto [i1, j1] = validStacks[choice1 - 1];
    auto [i2, j2] = validStacks[choice2 - 1];

    std::vector<int> tempStack1, tempStack2;

    for (int k = 0; k < boardSize; ++k) {
        if (board[i1][j1][k] != 0) tempStack1.push_back(board[i1][j1][k]);
        if (board[i2][j2][k] != 0) tempStack2.push_back(board[i2][j2][k]);
        board[i1][j1][k] = 0;
        board[i2][j2][k] = 0;
    }

    for (int k = 0; k < static_cast<int>(tempStack1.size()); ++k) {
        board[i2][j2][k] = tempStack1[k];
    }
    for (int k = 0; k < static_cast<int>(tempStack2.size()); ++k) {
        board[i1][j1][k] = tempStack2[k];
    }

    std::cout << "Teancurile de la pozițiile (" << i1 << ", " << j1 << ") și (" << i2 << ", " << j2 << ") au fost interschimbate.\n";
}

void Elemente::ceata(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    if (currentPlayer.ceckIluzie) {
        std::cout << "Nu poți avea două iluzii simultan pe tablă.\n";
        return;
    }

    int i, j;
    std::cout << "Alege poziția pentru a plasa o nouă iluzie (i și j între 0 și " << boardSize - 1 << "):\n";
    std::cout << "i: ";
    std::cin >> i;
    std::cout << "j: ";
    std::cin >> j;

    if (i < 0 || i >= boardSize || j < 0 || j >= boardSize) {
        std::cout << "Poziție invalidă.\n";
        return;
    }

    int k = Functions::lastK(i, j, board);
    if (k < 0 || k >= boardSize || board[i][j][k] != 0) {
        std::cout << "Nu există spațiu liber pentru a plasa o iluzie la poziția aleasă.\n";
        return;
    }

    board[i][j][k] = 1;
    currentPlayer.ceckIluzie = true;

    std::cout << "Iluzia a fost plasată la poziția (" << i << ", " << j << ").\n";
}


void Elemente::val(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    std::cout << "Alege un teanc de carti de mutat pe o pozitie adiacentă goală:\n";

    std::vector<std::pair<int, int>> validStacks;

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            int count = 0;
            for (int k = 0; k < boardSize; ++k)
            {
                if (board[i][j][k] != 0)
                {
                    ++count;
                }
            }

            if (count > 0)
            {
                validStacks.push_back({ i, j });
            }
        }
    }

    if (validStacks.empty())
    {
        std::cout << "Nu exista teancuri de carti pe tabla.\n";
        return;
    }

    std::cout << "Teancuri disponibile:\n";
    for (size_t index = 0; index < validStacks.size(); ++index)
    {
        int i = validStacks[index].first;
        int j = validStacks[index].second;
        std::cout << "Teancul de la pozitia (" << i << ", " << j << ")\n";
    }

    int choice;
    std::cout << "Alege un teanc de carti (1-" << validStacks.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > validStacks.size())
    {
        std::cout << "Selectie invalida.\n";
        return;
    }

    int i = validStacks[choice - 1].first;
    int j = validStacks[choice - 1].second;

    std::cout << "Alege o pozitie adiacentă goală unde vrei să muți teancul:\n";
    int newI, newJ;

    std::cout << "Introdu noua pozitie i (0-" << boardSize - 1 << "): ";
    std::cin >> newI;
    std::cout << "Introdu noua pozitie j (0-" << boardSize - 1 << "): ";
    std::cin >> newJ;

    if (newI < 0 || newI >= boardSize || newJ < 0 || newJ >= boardSize)
    {
        std::cout << "Pozitie invalida.\n";
        return;
    }

    bool isAdjacent = (abs(i - newI) == 1 && j == newJ) || (abs(j - newJ) == 1 && i == newI);
    if (!isAdjacent)
    {
        std::cout << "Pozitia aleasă nu este adiacentă.\n";
        return;
    }

    bool isEmpty = true;
    for (int k = 0; k < boardSize; ++k)
    {
        if (board[newI][newJ][k] != 0)
        {
            isEmpty = false;
            break;
        }
    }

    if (!isEmpty)
    {
        std::cout << "Pozitia aleasă nu este goală.\n";
        return;
    }

    std::vector<int> tempStack;
    for (int k = 0; k < boardSize; ++k)
    {
        if (board[i][j][k] != 0)
        {
            tempStack.push_back(board[i][j][k]);
            board[i][j][k] = 0;
        }
    }

    for (size_t index = 0; index < tempStack.size(); ++index)
    {
        for (int k = 0; k < boardSize; ++k)
        {
            if (board[newI][newJ][k] == 0)
            {
                board[newI][newJ][k] = tempStack[index];
                break;
            }
        }
    }

    std::cout << "Teancul a fost mutat de la pozitia (" << i << ", " << j << ") la pozitia (" << newI << ", " << newJ << ").\n";
}

void Elemente::tsunami(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize)
{
    int row;
    std::cout << "Alege un rând pentru Tsunami (0-" << boardSize - 1 << "): ";
    std::cin >> row;

    if (row < 0 || row >= boardSize)
    {
        std::cout << "Rând invalid.\n";
        return;
    }

    bool spaceFound = false;
    for (int col = 0; col < boardSize; ++col)
    {
        if (board[row][col][Functions::lastK(row, col, board)] == 0)
        {
            spaceFound = true;
            break;
        }
    }

    if (!spaceFound)
    {
        std::cout << "Nu există spațiu gol pe acest rând pentru ca adversarul să plaseze o carte.\n";
        return;
    }

    opponent.restrictedRow = row;
    std::cout << "Tsunami activ pe rândul " << row << " pentru adversar.\n";
}


void Elemente::cascade(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int row;
    std::cout << "Alege un rând cu cel puțin 3 poziții ocupate: ";
    std::cin >> row;

    if (row < 0 || row >= boardSize) {
        std::cout << "Rând invalid. Alege un rând între 0 și " << boardSize - 1 << ".\n";
        return;
    }

    int occupiedCount = 0;
    for (int col = 0; col < boardSize; ++col) {
        if (board[row][col][0] != 0) {
            occupiedCount++;
        }
    }

    if (occupiedCount < 3) {
        std::cout << "Rândul ales nu are suficiente poziții ocupate pentru a aplica Cascadă.\n";
        return;
    }

    char direction;
    std::cout << "Alege direcția (L pentru stânga / D pentru dreapta): ";
    std::cin >> direction;

    if (direction == 'L' || direction == 'l') {
        int target = 0;
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col][0] != 0) {
                board[row][target][0] = board[row][col][0];
                if (target != col) {
                    board[row][col][0] = 0;
                }
                target++;
            }
        }
    }
    else if (direction == 'D' || direction == 'd') {
        int target = boardSize - 1;
        for (int col = boardSize - 1; col >= 0; --col) {
            if (board[row][col][0] != 0) {
                board[row][target][0] = board[row][col][0];
                if (target != col) {
                    board[row][col][0] = 0;
                }
                target--;
            }
        }
    }
    else {
        std::cout << "Direcție invalidă! Alege L pentru stânga sau D pentru dreapta.\n";
        return;
    }

    std::cout << "Cascada a fost aplicată cu succes pe rândul " << row << " în direcția " << (direction == 'L' || direction == 'l' ? "stânga" : "dreapta") << ".\n";
}



void Elemente::sprijin(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int cardValue;
    std::cout << "Alege o carte proprie cu valoarea 1, 2 sau 3: ";
    std::cin >> cardValue;

    bool found = false;
    for (int i = 0; i < currentPlayer.cards.size(); ++i) {
        if (currentPlayer.cards[i] == cardValue) {
            found = true;
            currentPlayer.cards[i]++;
            std::cout << "Valoarea cartii a fost crescuta cu 1!\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Nu ai o carte cu valoarea " << cardValue << " in mana ta.\n";
    }
}

void Elemente::cutremur(std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    bool found = false;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            for (int k = 0; k < boardSize; ++k) {
                if (board[i][j][k] == 1) {
                    board[i][j][k] = 0;
                    found = true;
                }
            }
        }
    }

    if (found) {
        std::cout << "Toate cărțile cu valoarea 1 au fost eliminate de pe tablă.\n";
    }
    else {
        std::cout << "Nu au fost găsite cărți cu valoarea 1 pe tablă.\n";
    }
}

void Elemente::sfarimare(Player& opponent, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int targetValue;
    std::cout << "Alege o valoare (2, 3, 4) pentru a o penaliza: ";
    std::cin >> targetValue;

    if (targetValue < 2 || targetValue > 4) {
        std::cout << "Valoare invalidă. Alegerea trebuie să fie 2, 3 sau 4.\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            for (int k = 0; k < boardSize; ++k) {
                if (board[i][j][k] == targetValue) {
                    board[i][j][k] -= 1;
                    found = true;
                    std::cout << "Valoarea cărții de la poziția (" << i << ", " << j << ", " << k << ") a fost scăzută cu 1.\n";
                    return;
                }
            }
        }
    }

    if (!found) {
        std::cout << "Nu s-a găsit nicio carte cu valoarea " << targetValue << " pe tablă.\n";
    }
}
void Elemente::granite(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int x, y;
    std::cout << "Alege poziția pentru cartea neutră (x și y între 0 și " << boardSize - 1 << "): ";
    std::cin >> x >> y;

    int dummyVar1 = 0;  
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        std::cout << "Poziție invalidă. Poziția trebuie să fie în limitele tablei.\n";
        return;
    }

    int k = Functions::lastK(x, y, board);
    int dummyVar2 = k; 
    if (k >= boardSize) {
        std::cout << "Poziția (" << x << ", " << y << ") este deja complet ocupată.\n";
        return;
    }

    board[x][y][k] = 0;
    int dummyVar3 = 1; 
    std::cout << "Cartea neutră a fost plasată la poziția (" << x << ", " << y << ").\n";

    int cardToPlay;
    std::cout << "Alege o carte din mână pentru a o juca pe tabla de joc: ";
    for (size_t i = 0; i < currentPlayer.cards.size(); ++i) {
        std::cout << currentPlayer.cards[i] << " ";
    }
    std::cout << "\n";
    std::cin >> cardToPlay;

    auto it = std::find(currentPlayer.cards.begin(), currentPlayer.cards.end(), cardToPlay);
    int dummyVar4 = 2;  
    if (it == currentPlayer.cards.end()) {
        std::cout << "Cartea aleasă nu se află în mână. Operațiunea a fost anulată.\n";
        return;
    }

    currentPlayer.cards.erase(it);
    board[x][y][k + 1] = cardToPlay;
    int dummyVar5 = cardToPlay;  
    std::cout << "Cartea " << cardToPlay << " a fost jucată la poziția (" << x << ", " << y << ").\n";
}


void Elemente::avalansa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int x1, y1, x2, y2;
    std::cout << "Alege coordonatele pentru primul teanc (x1 și y1 între 0 și " << boardSize - 1 << "): ";
    std::cin >> x1 >> y1;

    int dummyVar6 = 3;  
    std::cout << "Alege coordonatele pentru al doilea teanc (x2 și y2 între 0 și " << boardSize - 1 << "): ";
    std::cin >> x2 >> y2;

    if (!((x1 >= 0 && x1 < boardSize && y1 >= 0 && y1 < boardSize) &&
        (x2 >= 0 && x2 < boardSize && y2 >= 0 && y2 < boardSize))) {
        std::cout << "Coordonate invalide. Teancurile trebuie să fie în limitele tablei.\n";
        return;
    }

    if (!((x1 == x2 && abs(y1 - y2) == 1) || (y1 == y2 && abs(x1 - x2) == 1))) {
        std::cout << "Teancurile trebuie să fie adiacente pe orizontală sau verticală.\n";
        return;
    }

    int direction;
    std::cout << "Alege direcția de shiftare (1 - stânga, 2 - dreapta, 3 - sus, 4 - jos): ";
    std::cin >> direction;

    int dx = 0, dy = 0;
    int dummyVar7 = direction;  
    if (direction == 1) dy = -1;
    else if (direction == 2) dy = 1;
    else if (direction == 3) dx = -1;
    else if (direction == 4) dx = 1;
    else {
        std::cout << "Direcție invalidă. Operațiunea a fost anulată.\n";
        return;
    }

    if (!((x1 + dx >= 0 && x1 + dx < boardSize && y1 + dy >= 0 && y1 + dy < boardSize) &&
        (x2 + dx >= 0 && x2 + dx < boardSize && y2 + dy >= 0 && y2 + dy < boardSize) &&
        board[x1 + dx][y1 + dy][0] == 0 && board[x2 + dx][y2 + dy][0] == 0)) {
        std::cout << "Direcția aleasă nu este validă. Pozițiile destinație trebuie să fie goale.\n";
        return;
    }

    for (int k = Functions::lastK(x1, y1, board); k >= 0; --k) {
        board[x1 + dx][y1 + dy][k] = board[x1][y1][k];
        board[x1][y1][k] = 0;
    }

    for (int k = Functions::lastK(x2, y2, board); k >= 0; --k) {
        board[x2 + dx][y2 + dy][k] = board[x2][y2][k];
        board[x2][y2][k] = 0;
    }

    std::cout << "Teancurile au fost mutate în direcția aleasă.\n";
}


void Elemente::bolovan(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    if (!currentPlayer.ceckIluzie) {
        std::cout << "Această putere este disponibilă doar dacă se joacă jocul cu iluzii.\n";
        return;
    }

    int x, y;
    std::cout << "Alege coordonatele iluziei pe care dorești să o acoperi (x și y între 0 și " << boardSize - 1 << "): ";
    std::cin >> x >> y;

    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        std::cout << "Coordonate invalide. Iluzia trebuie să fie pe tabla de joc.\n";
        return;
    }

    int topCardIndex = Functions::lastK(x, y, board);
    if (topCardIndex == -1 || board[x][y][topCardIndex] >= 0) {
        std::cout << "La coordonatele selectate nu există o iluzie care să poată fi acoperită.\n";
        return;
    }

    if (currentPlayer.cards.empty()) {
        std::cout << "Nu ai cărți în mână pentru a acoperi iluzia.\n";
        return;
    }

    std::cout << "Alege o carte din mână pentru a acoperi iluzia:\n";
    for (size_t i = 0; i < currentPlayer.cards.size(); ++i) {
        std::cout << i + 1 << ". " << currentPlayer.cards[i] << "\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(currentPlayer.cards.size())) {
        std::cout << "Alegere invalidă. Operațiunea a fost anulată.\n";
        return;
    }

    int selectedCard = currentPlayer.cards[choice - 1];
    board[x][y][topCardIndex + 1] = selectedCard; 
    currentPlayer.cards.erase(currentPlayer.cards.begin() + choice - 1);

    std::cout << "Cartea " << selectedCard << " a fost plasată deasupra iluziei la poziția (" << x << ", " << y << ").\n";
}


void Elemente::vartejDeApa(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    int selectedRow = -1;
    std::cout << "Alege un rand pentru Vartejul de apă (0-" << boardSize - 1 << "): ";
    std::cin >> selectedRow;

    if (selectedRow < 0 || selectedRow >= boardSize) {
        std::cout << "Rand invalid. Operatiunea a fost anulata.\n";
        return;
    }

    std::vector<std::pair<int, int>> cardsOnRow;
    int emptyColumn = -1;


    for (int col = 0; col < boardSize; ++col) {
        if (board[selectedRow][col][0] != 0) {
            cardsOnRow.push_back({ col, board[selectedRow][col][0] });
        }
        else {
            if (emptyColumn == -1) {
                emptyColumn = col;
            }
        }
    }

    if (cardsOnRow.size() != 2 || emptyColumn == -1) {
        std::cout << "Randul selectat nu are exact doua carti separate de un spațiu gol.\n";
        return;
    }


    int firstCard = cardsOnRow[0].second;
    int secondCard = cardsOnRow[1].second;

    int topCard = (abs(firstCard) > abs(secondCard)) ? firstCard : secondCard;
    int bottomCard = (abs(firstCard) > abs(secondCard)) ? secondCard : firstCard;


    if (abs(firstCard) == abs(secondCard)) {
        std::cout << "Ambele carti au aceeasi valoare. Care dintre ele vrei sa fie deasupra?\n";
        std::cout << "1. Cartea de la coloana " << cardsOnRow[0].first << "\n";
        std::cout << "2. Cartea de la coloana " << cardsOnRow[1].first << "\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            topCard = firstCard;
            bottomCard = secondCard;
        }
        else {
            topCard = secondCard;
            bottomCard = firstCard;
        }
    }

    
    board[selectedRow][emptyColumn][0] = bottomCard;
    board[selectedRow][emptyColumn][1] = topCard;   

    
    board[selectedRow][cardsOnRow[0].first][0] = 0;
    board[selectedRow][cardsOnRow[1].first][0] = 0;

    std::cout << "Cartile au fost mutate pe coloana " << emptyColumn << " din randul " << selectedRow << ".\n";
}
void Elemente::ecouEtern(Player& currentPlayer, std::vector<std::vector<std::vector<int>>>& board, int boardSize) {
    std::cout << "Alege un teanc de pe tabla pentru a copia ultima carte vizibila:\n";

    std::vector<std::pair<int, int>> validStacks;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int lastCardIndex = Functions::lastK(i, j, board);
            if (lastCardIndex != -1) { 
                validStacks.push_back({ i, j });
            }
        }
    }

    if (validStacks.empty()) {
        std::cout << "Nu există teancuri cu cărți vizibile pe tablă.\n";
        return;
    }

    std::cout << "Teancuri disponibile:\n";
    for (size_t index = 0; index < validStacks.size(); ++index) {
        int i = validStacks[index].first;
        int j = validStacks[index].second;
        int lastCardIndex = Functions::lastK(i, j, board);
        std::cout << index + 1 << ". Teancul de la pozitia (" << i << ", " << j
            << ") cu ultima carte: " << board[i][j][lastCardIndex] << "\n";
    }

    int choice;
    std::cout << "Alege teancul (1-" << validStacks.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(validStacks.size())) {
        std::cout << "Selectie invalida.\n";
        return;
    }

    int i = validStacks[choice - 1].first;
    int j = validStacks[choice - 1].second;
    int lastCardIndex = Functions::lastK(i, j, board);

    int cardValue = board[i][j][lastCardIndex];
    currentPlayer.cards.push_back(cardValue);

    std::cout << "Ai copiat cartea " << cardValue << " din teancul de la pozitia (" << i << ", " << j << ").\n";
}



