#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono> 
#include "Wizzard.h"
#include "Elemente.h"
#include"Functions.h"

using namespace std;

Game::Game(int size, GameMode currentMode, std::string elem1) : boardSize(size) {
	board = std::vector<std::vector<std::vector<int>>>(size, std::vector<std::vector<int>>(size, std::vector<int>(4, 0)));
	Mode = currentMode;
	std::srand(static_cast<unsigned int>(std::time(0)));
	

	player1.color = BLUE;
	player1.symbol = 'A';

	player2.color = RED;
	player2.symbol = 'B';
	switch (Mode) {
	case GameMode::Modul_antrenament:
		
		player1.cards = { 1, 1, 2, 2, 3, 3, 4 };
		player2.cards = { 1, 1, 2, 2, 3, 3, 4 };
		totalRounds = 3;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		break;
	case GameMode::Duelul_vrajitorilor:
		
		std::this_thread::sleep_for(std::chrono::seconds(2));
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		totalRounds = 5;
		needWizz = true;
		break;
	case GameMode::Duelul_elementelor:
		
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		totalRounds = 5;
		needElement = true;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		break;
	case GameMode::Duelul_elemWizz:
		
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		totalRounds = 5;
		needWizz = true;
		needElement = true;
		break;
	default:
		std::cout << "Mod necunoscut!" << std::endl;
		break;
	}
	if (needWizz) {
		int RandomWizz = std::rand() % 8;
		switch (RandomWizz) {
		case 0:
			player1.wizardName = "Eliminatorul";
			break;
		case 1:
			player1.wizardName = "Maestrul Eterului";
			break;
		case 2:
			player1.wizardName = "Distrugatorul de Randuri";
			break;
		case 3:
			player1.wizardName = "Transformatorul de Spatii";
			break;
		case 4:
			player1.wizardName = "Muta Teancuri";
			break;
		case 5:
			player1.wizardName = "Muta Teancuri Adversar";
			break;
		case 6:
			player1.wizardName = "Acopera Carti";
			break;
		case 7:
			player1.wizardName = "Transportatorul de Randuri";
			break;
		default:
			std::cout << "Alegere invalida!\n";
			break;
		}

		int RandomWizz2 = std::rand() % 8;
		switch (RandomWizz2) {
		case 0:
			player2.wizardName = "Eliminatorul";
			break;
		case 1:
			player2.wizardName = "Maestrul Eterului";
			break;
		case 2:
			player2.wizardName = "Distrugatorul de Randuri";
			break;
		case 3:
			player2.wizardName = "Transformatorul de Spatii";
			break;
		case 4:
			player2.wizardName = "Muta Teancuri";
			break;
		case 5:
			player2.wizardName = "Muta Teancuri Adversar";
			break;
		case 6:
			player2.wizardName = "Acopera Carti";
			break;
		case 7:
			player2.wizardName = "Transportatorul de Randuri";
			break;
		}
	}
	if (needElement) {
		element1 = elem1;
		element1 = elem1;
		std::srand(static_cast<unsigned>(std::time(0)));
		int index1 = std::rand() % 23;
		int index2 = std::rand() % 23;
		while (index1 == index2) {
			index2 = std::rand() % 23;
		}
		switch (index1) {
		case 0: element1 = "distrugere"; break;
		case 1: element1 = "flacari"; break;
		case 2: element1 = "lava"; break;
		case 3: element1 = "dinCenusa"; break;
		case 4: element1 = "scantei"; break;
		case 5: element1 = "vifor"; break;
		case 6: element1 = "vijelie"; break;
		case 7: element1 = "uragan"; break;
		case 8: element1 = "rafala"; break;
		case 9: element1 = "miraj"; break;
		case 10: element1 = "furtuna"; break;
		case 11: element1 = "maree"; break;
		case 12: element1 = "ceata"; break;
		case 13: element1 = "val"; break;
		case 14: element1 = "tsunami"; break;
		case 15: element1 = "cascade"; break;
		case 16: element1 = "sprijin"; break;
		case 17: element1 = "cutremur"; break;
		case 18: element1 = "sfarimare"; break;
		case 19: element1 = "granite"; break;
		case 20: element1 = "avalansa"; break;
		case 21: element1 = "bolovan"; break;
		case 22: element1 = "vartejDeApa"; break;
		default: element1 = "necunoscut"; break;
		}

		switch (index2) {
		case 0: element2 = "distrugere"; break;
		case 1: element2 = "flacari"; break;
		case 2: element2 = "lava"; break;
		case 3: element2 = "dinCenusa"; break;
		case 4: element2 = "scantei"; break;
		case 5: element2 = "vifor"; break;
		case 6: element2 = "vijelie"; break;
		case 7: element2 = "uragan"; break;
		case 8: element2 = "rafala"; break;
		case 9: element2 = "miraj"; break;
		case 10: element2 = "furtuna"; break;
		case 11: element2 = "maree"; break;
		case 12: element2 = "ceata"; break;
		case 13: element2 = "val"; break;
		case 14: element2 = "tsunami"; break;
		case 15: element2 = "cascade"; break;
		case 16: element2 = "sprijin"; break;
		case 17: element2 = "cutremur"; break;
		case 18: element2 = "sfarimare"; break;
		case 19: element2 = "granite"; break;
		case 20: element2 = "avalansa"; break;
		case 21: element2 = "bolovan"; break;
		case 22: element2 = "vartejDeApa"; break;
		default: element2 = "necunoscut"; break;
		}
	}
	isPlayer1Turn = true;
}



void Game::printCentered(const std::string& text, const std::string& alignment)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	int position = 0;
	if (alignment == "center") {
		position = (consoleWidth - (text.length() / 2)) / 2;
	}
	else if (alignment == "right") {
		position = consoleWidth - text.length();
	}
	else if (alignment == "left") {
		position = 0;
	}

	COORD coord = { position, csbi.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << text;
}

void Game::printCenteredforBoard(const std::string& text, int ok)
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

int Game::lastK(int i, int j)
{
	int k = 0;
	while (board[i][j][k] != 0) { k++; };
	if (k == 0) { return  k; }
	return  k -= 1;

}

void Game::iluzie(int i, int j, int cardValue, int turns, Player& currentPlayer, int cardIndex)
{
	while (board[i][j][lastK(i, j)] != 0 || i < 0 || i >= boardSize || j < 0 || j >= boardSize || turns > 0 && !isAdjacent(i, j)) {
		cout << "Pozitia este ocupata. Alegeti alta  pozitie pemtru iluzie (linie si coloana): ";
		cin >> i >> j;
	}

	board[i][j][0] = isPlayer1Turn ? cardValue : -cardValue;;
	if (board[i][j][0] > 0) { board[i][j][1] = 11; }
	else { board[i][j][1] = -11; }
	currentPlayer.cards.erase(currentPlayer.cards.begin() + cardIndex);
	currentPlayer.LastPoz.i = i;
	currentPlayer.LastPoz.j = j;
	currentPlayer.LastPoz.k = lastK(i, j);
	currentPlayer.symbol = 'A' ? player2.ceckIluzie = true : player1.ceckIluzie = true;
}

void Game::displayBoard(int n1, int n2, int ok) {
	system("cls");
	printCentered("Jucatorul 1", "left");
	printCentered("Jucatorul 2", "right");
	cout << endl;
	string score1 = "Vicotrii = ";
	string score2 = "Vicotrii = ";
	score1 += to_string(currentPlayer.totalscore);
	score2 += to_string(opponent.totalscore);
	if (currentPlayer.symbol == 'A') {
	printCentered(score1, "left");
	printCentered(score2, "right");
	}
	else {
		printCentered(score2, "left");
	    printCentered(score1, "right");
	}
	cout << endl;
	if (needWizz) {
		string poz1, poz2;
		if (currentPlayer.symbol == 'A') {
			poz1 = "left";
			poz2 = "right";
		}
		else {
			poz2 = "left";
			poz1 = "right";
		}
		if (currentPlayer.wizardName == "Eliminatorul") {
			printCentered("are vrajitorul Eliminatorul: ", poz1);
		}
		else if (currentPlayer.wizardName == "Maestrul Eterului") {
			printCentered("are vrajitorul: Maestrul Eterului", poz1);
		}
		else if (currentPlayer.wizardName == "Distrugatorul de Randuri") {
			printCentered("are vrajitorul: Distrugatorul de Randuri", poz1);
		}
		else if (currentPlayer.wizardName == "Transformatorul de Spatii") {
			printCentered("are vrajitorul: Transformatorul de Spatii", poz1);
		}
		else if (currentPlayer.wizardName == "Muta Teancuri") {
			printCentered("are vrajitorul: Muta Teancuri", poz1);
		}
		else if (currentPlayer.wizardName == "Muta Teancuri Adversar") {
			printCentered("are vrajitorul: Muta Teancuri Adversar", poz1);
		}
		else if (currentPlayer.wizardName == "Acopera Carti") {
			printCentered("are vrajitorul: Acopera Carti", poz1);
		}
		else if (currentPlayer.wizardName == "Transportatorul de Randuri") {
			printCentered("are vrajitorul: Transportatorul de Randuri", poz1);
		}

		if (opponent.wizardName == "Eliminatorul") {
			printCentered("are vrajitorul Eliminatorul: ", poz2);
		}
		else if (opponent.wizardName == "Maestrul Eterului") {
			printCentered("are vrajitorul: Maestrul Eterului", poz2);
		}
		else if (opponent.wizardName == "Distrugatorul de Randuri") {
			printCentered("are vrajitorul: Distrugatorul de Randuri", poz2);
		}
		else if (opponent.wizardName == "Transformatorul de Spatii") {
			printCentered("are vrajitorul: Transformatorul de Spatii", poz2);
		}
		else if (opponent.wizardName == "Muta Teancuri") {
			printCentered("are vrajitorul: Muta Teancuri", poz2);
		}
		else if (opponent.wizardName == "Muta Teancuri Adversar") {
			printCentered("are vrajitorul: Muta Teancuri Adversar", poz2);
		}
		else if (opponent.wizardName == "Acopera Carti") {
			printCentered("are vrajitorul: Acopera Carti", poz2);
		}
		else if (opponent.wizardName == "Transportatorul de Randuri") {
			printCentered("are vrajitorul: Transportatorul de Randuri", poz2);
		}
		cout << endl;
	}
	printCentered(" carti: ", "left");
	printCentered("carti: ", "right");
	cout << endl;
	std::string cards1;
	std::string cards2;
	for (int card : player1.cards) {
		if (card == 9) {
			cards1 += "E ";
		}
		else {
			cards1 += std::to_string(card) + " ";
		}
	}
	for (int card2 : player2.cards) {
		if (card2 == 9) {
			cards2 += "E ";
		}
		else {
			cards2 += std::to_string(card2) + " ";
		}
	}
	if (currentPlayer.symbol == 'A') {
	cout << currentPlayer.color;
	printCentered(cards1, "left");
	cout << RESET;
	cout << opponent.color;
	printCentered(cards2, "right");
	cout << RESET;
	}
	else {
		cout << opponent.color;
		printCentered(cards2, "left");
		cout << RESET;
		cout << currentPlayer.color;
		printCentered(cards1, "right");
		cout << RESET;
	}
	//cout << endl;
	cards1 = "";
	cards2 = "";
	if (needElement) {
		printCentered("Cele 2 elemente sunt: ", "center");
		cout << endl;
		printCentered(element1, "center");
		cout << endl;
		printCentered(element2, "center");
		cout << endl;
	}
	printCentered("Tabla de joc : ", "center"); cout << "\n\n\n";
	int difSize=3;
	if (boardSize == 7) {
		difSize = 4;
	}
	int i;
	for ((ok == 1 ? i = n1 : i = 0); (ok == 1 ? i < n1 + difSize : i < boardSize); i++) {
		for (int j = n2 - (difSize-1); j <= n2; j++) {
			if (board[i][j][0] == 0) {
				if (j == n2 - (difSize-1)) {
					printCenteredforBoard(" ", ok);
				}
				if (ok == 1) {
					cout << "[ ]";
				}
				else {
					cout << "   ";
				}
			}
			else {
				if (j == n2 - (difSize - 1)) {
					printCenteredforBoard(" ", ok);
				}
				int k = lastK(i, j);
				int cellValue = board[i][j][k];
				switch (cellValue) {
				case 9:
					cout << BLUE << "[E]" << RESET;
					break;
				case -9:
					cout << RED << "[E]" << RESET;
					break;
				case 11:
					cout << BLUE << "[#]" << RESET;
					break;
				case -11:
					cout << RED << "[#]" << RESET;
					break;
				case 15:
					cout << BLUE << "[@]" << RESET;
					break;
				case -15:
					cout << RED << "[@]" << RESET;
					break;
				default:
					if (cellValue > 0) {
						cout << BLUE << "[" << cellValue << "]" << RESET;
					}
					else {
						cout << RED << "[" << -cellValue << "]" << RESET;
					}
					break;
				}

			}
		}
		cout << endl;
	}
	cout <<"\n\n\n";
	if (ok == 1 && boardSize==5) {
	printCentered("Cartea explozie: ", "center");
	cout << endl;
	EX.afisare_carte_explozie_3x3(CE , ok, boardSize);
	cout << "\n";
	printCentered("Legenda:", "center");
	cout << endl;
	printCentered(" 1.Elimina cartea din joc - acea carte nu mai poate fi folosita", "center");
	cout << endl; 
	printCentered("2.Intoarce cartea in mana proprietarului                     ", "center");
	cout << endl;
	printCentered("3.Creeaza o groapa                                         ", "center");
	cout << "\n\n\n";
	}

	if (ok == 1 && boardSize == 7) {
		printCentered("Cartea explozie: ", "center");
		cout << endl;
		EX.afisare_carte_explozie_4x4(CE, ok, boardSize);
		cout << "\n";
		printCentered("Legenda:", "center");
		cout << endl;
		printCentered(" 1.Elimina cartea din joc - acea carte nu mai poate fi folosita", "center");
		cout << endl;
		printCentered("2.Intoarce cartea in mana proprietarului                     ", "center");
		cout << endl;
		printCentered("3.Creeaza o groapa                                         ", "center");
		cout << "\n\n\n";
	}


}


bool Game::checkRow() {
	int row = 0;

	for (int i = 0; i < boardSize; i++) {
		bool hasNonZero = false;
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j][lastK(i, j)] != 0) {
				hasNonZero = true;
				break;
			}
			if (hasNonZero) {
				break;
			}
		}
		if (hasNonZero) row++;
	}




	if (boardSize == 5 && row == 3) {
		return true;
	}
	else if (boardSize == 7 && row == 4) {
		return true;
	}
	return false;
}

bool Game::checkCol()
{
	int col = 0;
	for (int j = 0; j < boardSize; j++) {
		bool hasNonZero = false;
		for (int i = 0; i < boardSize; i++) {
			for (int k = 0; k < 4; k++) {
				if (board[i][j][k] != 0) {
					hasNonZero = true;
					break;
				}
			}
			if (hasNonZero) {
				break;
			}
		}
		if (hasNonZero) col++;
	}
	if (boardSize == 5 && col == 3) {
		return true;
	}
	else if (boardSize == 7 && col == 4) {
		return true;
	}
	return false;
}

int Game::checkRowForWizz(int n1, int n2, int ok)
{
	int row = 0;
	if (boardSize == 5) {
		switch (row) {
		case 0:row = n1;
			break;
		case 1:row = n1 + 1;
			break;
		case 2:row = n1 + 2;
			break;
		}
	}
	else if (boardSize == 7) {
		switch (row) {
		case 0:row = n1;
			break;
		case 1:row = n1 + 1;
			break;
		case 2:row = n1 + 2;
			break;
		case 3:row + n1 + 3;
			break;
		}
	}
	int i;
	for ((ok == 1 ? i = n1 : i = 0); (ok == 1 ? i < n1 + 3 : i < boardSize); i++) {
		for (int j = n2 - 2; j <= n2; j++) {
			for (int k = 0; k < 4; k++) {
				if (board[i][j][k] != 0) {
					row++;
				}
			}
		}
	}
	return row;

}

int Game::checkWin(Player& player, int n1, int n2, int turns, int ok) {
	int val = (player.symbol == 'A') ? 1 : -1;
	if (boardSize == 5) {
		for (int i = 0; i < 3; i++) {

			if (board[n1 + i][n2 - 2][lastK(n1 + i, n2 - 2)] > 0 &&
				board[n1 + i][n2 - 1][lastK(n1 + i, n2 - 1)] > 0 &&
				board[n1 + i][n2][lastK(n1 + i, n2)] > 0) {
				return 1;
			}
			if (board[n1 + i][n2 - 2][lastK(n1 + i, n2 - 2)] < 0 &&
				board[n1 + i][n2 - 1][lastK(n1 + i, n2 - 1)] < 0 &&
				board[n1 + i][n2][lastK(n1 + i, n2)] < 0) {
				return 1;
			}

		}
		for (int j = 0; j < 3; j++) {
			if (board[n1][n2 - 2 + j][lastK(n1, n2 - 2 + j)] > 0 &&
				board[n1 + 1][n2 - 2 + j][lastK(n1 + 1, n2 - 2 + j)] > 0 &&
				board[n1 + 2][n2 - 2 + j][lastK(n1 + 2, n2 - 2 + j)] > 0) {
				return 1;
			}
			if (board[n1][n2 - 2 + j][lastK(n1, n2 - 2 + j)] < 0 &&
				board[n1 + 1][n2 - 2 + j][lastK(n1 + 1, n2 - 2 + j)] < 0 &&
				board[n1 + 2][n2 - 2 + j][lastK(n1 + 2, n2 - 2 + j)] < 0) {
				return 1;
			}
		}

		if (board[n1][n2 - 2][lastK(n1, n2 - 2)] > 0 &&
			board[n1 + 1][n2 - 1][lastK(n1 + 1, n2 - 1)] > 0 &&
			board[n1 + 2][n2][lastK(n1 + 2, n2)] > 0) {
			return 1;
		}
		if (board[n1][n2][lastK(n1, n2)] > 0 &&
			board[n1 + 1][n2 - 1][lastK(n1 + 1, n2 - 1)] > 0 &&
			board[n1 + 2][n2 - 2][lastK(n1 + 2, n2 - 2)] > 0) {
			return 1;
		}

		if (board[n1][n2 - 2][lastK(n1, n2 - 2)] < 0 &&
			board[n1 + 1][n2 - 1][lastK(n1 + 1, n2 - 1)] < 0 &&
			board[n1 + 2][n2][lastK(n1 + 2, n2)] < 0) {
			return 1;
		}
		if (board[n1][n2][lastK(n1, n2)] < 0 &&
			board[n1 + 1][n2 - 1][lastK(n1 + 1, n2 - 1)] < 0 &&
			board[n1 + 2][n2 - 2][lastK(n1 + 2, n2 - 2)] < 0) {
			return 1;
		}
		if (turns == 3 * 3 && ok == 1) {
			cout << "Jocul s-a terminat! ";
			if (player1.score > player2.score) {
				cout << "Jucatorul 1 a castigat prin puncte!\n";
				return 0;
			}
			else if (player2.score > player1.score) {
				cout << "Jucatorul 2 a castigat prin puncte!\n";
				return 0;
			}
			else {
				cout << "Este egalitate!\n";
				return 0;
			}
		}

	}
	else {
		for (int i = 0; i < 4; i++) {
			if (board[n1 + i][n2 - 3][lastK(n1 + i, n2 - 3)] > 0 && board[n1 + i][n2 - 2][lastK(n1 + i, n2 - 2)] > 0 &&
				board[n1 + i][n2 - 1][lastK(n1 + i, n2 - 1)] > 0 &&
				board[n1 + i][n2][lastK(n1 + i, n2)] > 0) {
				return 1;
			}
			if (board[n1 + i][n2 - 3][lastK(n1 + i, n2 - 3)] < 0 && board[n1 + i][n2 - 2][lastK(n1 + i, n2 - 2)] < 0 &&
				board[n1 + i][n2 - 1][lastK(n1 + i, n2 - 1)] < 0 &&
				board[n1 + i][n2][lastK(n1 + i, n2)] < 0) {
				return 1;
			}
		}
		for (int j = 0; j < 3; j++) {
			if (board[n1][n2 - 3 + j][lastK(n1, n2 - 3 + j)] > 0 && board[n1 + 1][n2 - 3 + j][lastK(n1 + 1, n2 - 3 + j)] > 0 &&
				board[n1 + 2][n2 - 3 + j][lastK(n1 + 2, n2 - 3 + j)] > 0 &&
				board[n1 + 3][n2 - 3 + j][lastK(n1 + 3, n2 - 3 + j)] > 0) {
				return 1;
			}
			if (board[n1][n2 - 3 + j][lastK(n1, n2 - 3 + j)] < 0 && board[n1 + 1][n2 - 3 + j][lastK(n1 + 1, n2 - 3 + j)] < 0 &&
				board[n1 + 2][n2 - 3 + j][lastK(n1 + 2, n2 - 3 + j)] < 0 &&
				board[n1 + 3][n2 - 3 + j][lastK(n1 + 3, n2 - 3 + j)] < 0) {
				return 1;
			}

		}
		if (board[n1][n2 - 3][lastK(n1, n2 - 3)] < 0 &&
			board[n1 + 1][n2 - 2][lastK(n1 + 1, n2 - 2)] < 0 &&
			board[n1 + 2][n2-1][lastK(n1 + 2, n2-1)] < 0 &&
			board[n1 + 3][n2][lastK(n1 + 2, n2)] < 0) {
			return 1;
		}
		if (board[n1][n2 - 3][lastK(n1, n2 - 3)] > 0 &&
			board[n1 + 1][n2 - 2][lastK(n1 + 1, n2 - 2)] > 0 &&
			board[n1 + 2][n2 - 1][lastK(n1 + 2, n2 - 1)] > 0 &&
			board[n1 + 3][n2][lastK(n1 + 2, n2)] > 0) {
			return 1;
		}

		if (turns == 4 * 4 && ok == 1) {
			cout << "Jocul s-a terminat! ";
			if (player1.score > player2.score) {
				cout << "Jucatorul 1 a castigat prin puncte!\n";
				return 0;
			}
			else if (player2.score > player1.score) {
				cout << "Jucatorul 2 a castigat prin puncte!\n";
				return 0;
			}
			else {
				cout << "Este egalitate!\n";
				return 0;
			}
		}
	}
	return false;
}

bool Game::isAdjacent(int row, int col) {


	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j][lastK(i, j)] != 0 && abs(row - i) <= 1 && abs(col - j) <= 1) {
				return true;
			}
		}
	}
	return false;
}
void Game::addSize(int& n1, int& n2)
{
	if (boardSize == 7) {
		n1 = 3;
		n2 = 3;
	}
	else {
		n1 = 2;
		n2 = 2;
	}
}

void Game::selectCard(Player& currentPlayer, int& row, int& col, int& cardIndex, int turns, int& cardValue, int ok, int n1, int n2)
{
	int iterator = 0;
	for (int i = currentPlayer.cards.size() - 1; i >= 0; i--) {
		if (currentPlayer.cards[i] == 9) {
			iterator += 1;
		}
		else {
			break;
		}
	}
	cout << "Selectati o carte (" << currentPlayer.cards[0] << "-" << currentPlayer.cards[currentPlayer.cards.size() - iterator - 1] << ") sau E(eter): ";
	cardIndex = -1;
	char value;
	cin >> value;
	if (value == 'E' || value == 'e') {
		cardValue = 9;
	}
	else
	{
		cardValue = value - '0';
	}
	for (int i = 0; i < currentPlayer.cards.size(); i++) {
		if (currentPlayer.cards[i] == abs(cardValue)) {
			cardIndex = i;
			break;
		}
	}

	if (cardIndex == -1) {
		cout << "Nu mai exsita carti cu valoarea " << cardValue << " te rog incerca alta valoare\n";
		selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
	}
	else if (turns != 0) {
		cout << "Alegeti pozitia (linie si coloana): ";
		cin >> row >> col;
		boolean isPlacedOk = true;
		do {
			if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || cardIndex < 0 || cardIndex >= currentPlayer.cards.size()) {
				cout << "Pozitie invalida. Incercati din nou.\n";
				isPlacedOk = false;
				cout << "Alegeti pozitia (linie si coloana): ";
				cin >> row >> col;
			}
			else if (turns > 0 && !isAdjacent(row, col)) {
				cout << "Trebuie sa plasati cartea in apropierea unei alte carti deja plasate. Incercati din nou.\n";
				isPlacedOk = false;
				cout << "Alegeti pozitia (linie si coloana): ";
				cin >> row >> col;
			}else if (checkRow() && !checkCol()) {
				if (row<n1 || row>n1 + 2) {
					cout << "Numarul de randuri a maxim a fost atins, trebuie sa plasezi cartea pe randurile deja existente\n";
					isPlacedOk = false;
					cout << "Alegeti pozitia (linie si coloana): ";
					cin >> row >> col;
				}
			}else if (!checkRow() && checkCol()) {
				if (col<n2 - 2 || col > n2) {
					cout << "Numarul de coloane a maxim a fost atins, trebuie sa plasezi cartea pe coloanele deja existente\n";
					isPlacedOk = false;
					cout << "Alegeti pozitia (linie si coloana): ";
					cin >> row >> col;
				}
			}
			else {
				isPlacedOk = true;
			}

		} while (isPlacedOk == false);
	}
	else {
		row = 2;
		col = 2;
		if (boardSize == 7) {
			row = 3, col = 3;
		}
	}

	if (ok == 1) {
		if (boardSize == 5) {
			translatatePozFor3x3(row, col, n1, n2);
		}
		if (boardSize == 7) {
			translatatePozFor4x4(row, col, n1, n2);
		}
	}
}

void Game::translatatePozFor3x3(int& row, int& col, int n1, int n2)
{
	switch (row) {
	case 0:row = n1;
		break;
	case 1:row = n1 + 1;
		break;
	case 2:row = n1 + 2;
		break;
	}
	switch (col) {
	case 0:col = n2 - 2;
		break;
	case 1:col = n2 - 1;
		break;
	case 2:col = n2;
		break;
	}
}

void Game::translatatePozFor4x4(int& row, int& col, int n1, int n2)
{
	switch (row) {
	case 0:row = n1;
		break;
	case 1:row = n1 + 1;
		break;
	case 2:row = n1 + 2;
		break;
	case 3:row = n1 + 3;
		break;
	}
	switch (col) {
	case 0:col = n2 - 3;
		break;
	case 1:col = n2 - 2;
		break;
	case 2:col = n2 - 1;
		break;
	case 3:col = n2;
		break;
	}
}

void Game::addCardOnBoard(int row, int col, Player& opponent, Player& currentPlayer, int cardValue, int& turns, int cardIndex)
{
	if (board[row][col][lastK(row, col)] != 0) {
		opponent.score -= abs(board[row][col][lastK(row, col)]);
		board[row][col][lastK(row, col) + 1] = (isPlayer1Turn ? cardValue : -cardValue);
		currentPlayer.score += cardValue;
	}
	else {
		board[row][col][lastK(row, col)] = (isPlayer1Turn ? cardValue : -cardValue);
		currentPlayer.score += cardValue;
	}

	currentPlayer.cards.erase(currentPlayer.cards.begin() + cardIndex);
	
	turns++;
}

int Game::addCard(int row, int col, Player& opponent, Player& currentPlayer, int cardValue, int& turns, int cardIndex)
{
	if ((board[row][col][lastK(row, col)] == 0 || abs(board[row][col][lastK(row, col)]) < cardValue) && abs(cardValue) != 9) {
		addCardOnBoard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex);
		currentPlayer.LastPoz.i = row;
		currentPlayer.LastPoz.j = col;
		currentPlayer.LastPoz.k = lastK(row, col);
		return 0;

	}
	else if (abs(cardValue) == 9) {
		if (board[row][col][lastK(row, col)] == 0) {
			addCardOnBoard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex);
			currentPlayer.LastPoz.i = row;
			currentPlayer.LastPoz.j = col;
			currentPlayer.LastPoz.k = lastK(row, col);
			return 0;
		}
		else if (cardValue == 9 && board[row][col][lastK(row, col)] != 0) {
			cout << "Nu se poate plasa cartea Eter, aceasta poate fi plasata doar pe o pozitie goala. Incercati din nou.\n";
			return 1;
		}
	}
	else if (abs(board[row][col][lastK(row, col)]) == 11) {
		board[row][col][lastK(row, col)] = 0;
		if (abs(cardValue) > abs(board[row][col][lastK(row, col)])) {
			addCardOnBoard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex);
			currentPlayer.LastPoz.i = row;
			currentPlayer.LastPoz.j = col;
			currentPlayer.LastPoz.k = lastK(row, col);
			cout << "Cartea " << (isPlayer1Turn ? player1.color : player2.color) << (isPlayer1Turn ? "jucatorului 1" : "jucatorului 2") << RESET << " este mai mare decat cartea de sub iluzie si a inlcuit-o\n";
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return 0;
		}
		else {
			cout << "Cartea " << (isPlayer1Turn ? player1.color : player2.color) << (isPlayer1Turn ? "jucatorului 1" : "jucatorului 2") << RESET << " este mai mica decat cartea de sub iluzie si a fost stearsa\n";
			currentPlayer.cards.erase(currentPlayer.cards.begin() + cardIndex);
			isPlayer1Turn = !isPlayer1Turn;
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return 0;
		}

	}
	else {
		cout << "Nu se poate plasa cartea. Incercati din nou.\n";
		return 1;
	}

}

void Game::resetGameState(int size)
{
	player1.cards.clear();
	player2.cards.clear();
	switch (Mode) {
	case GameMode::Modul_antrenament:
		player1.cards = { 1, 1, 2, 2, 3, 3, 4 };
		player2.cards = { 1, 1, 2, 2, 3, 3, 4 };
		break;
	case GameMode::Duelul_vrajitorilor:
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		break;
	case GameMode::Duelul_elementelor:
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		break;
	case GameMode::Duelul_elemWizz:
		player1.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		player2.cards = { 1, 1, 2, 2, 2, 3, 3, 3, 4, 9 };
		break;
	}
	player1.ceckIluzie = false;
	player2.ceckIluzie = false;
	player1.LastPoz.i = -1;
	player1.LastPoz.j = -1;
	player1.LastPoz.k = -1;
	player2.LastPoz.i = -1;
	player2.LastPoz.j = -1;
	player2.LastPoz.k = -1;
	board = std::vector<std::vector<std::vector<int>>>(size, std::vector<std::vector<int>>(size, std::vector<int>(4, 0)));
	isPlayer1Turn = true;
}


bool check2xForExplosion(vector<vector<vector<int>>>& matrix, int n1, int n2, int boardsize) {

	if (boardsize==5)
	{
		int filledrows = 0;
		int filledcolumns = 0;

		for (int i = n1; i <= n1 + 2; i++)
		{
			int ok = 1;
			for (int j = n2 - 2; j <= n2; j++)
			{
				if (matrix[i][j][0] == 0)
				{
					ok = 0;
				}

			}
			if (ok == 1)
				filledrows++;
		}

		for (int j = n2 - 2; j <= n2; j++)
		{
			int ok = 1;

			for (int i = n1; i <= n1 + 2; i++)
			{
				if (matrix[i][j][0] == 0)
				{
					ok = 0;
				}

			}
			if (ok == 1)
				filledcolumns++;
		}

		if (filledrows >= 2 || filledcolumns >= 2 || filledcolumns >= 1 && filledrows >= 1)
			return true;
	}

	else

		if (boardsize == 7)
		{
			int filledrows = 0;
			int filledcolumns = 0;

			for (int i = n1; i <= n1 + 3; i++)
			{
				int ok = 1;
				for (int j = n2 - 3; j <= n2; j++)
				{
					if (matrix[i][j][0] == 0)
					{
						ok = 0;
					}

				}
				if (ok == 1)
					filledrows++;
			}

			for (int j = n2 - 3; j <= n2; j++)
			{
				int ok = 1;

				for (int i = n1; i <= n1 + 3; i++)
				{
					if (matrix[i][j][0] == 0)
					{
						ok = 0;
					}

				}
				if (ok == 1)
					filledcolumns++;
			}

			if (filledrows >= 2 || filledcolumns >= 2 || filledcolumns >= 1 && filledrows >= 1)
				return true;
		}

	return false;

}

void Game::playGame() {
	while (player1.totalscore < totalRounds && player2.totalscore < totalRounds) {
		int turns = 0;
		int n1, n2;
		int ok = 0;
		addSize(n1, n2);


		if (player1.totalscore + player2.totalscore != 0) {
			resetGameState(boardSize);
			displayBoard(n1, n2, ok);
		}
		if (boardSize == 5) {
			CE = EX.generat_carte_explozie_3x3();
		}

		if(boardSize == 7 )
			CE = EX.generat_carte_explozie_4x4();



		while (true) {
			int row, col, cardIndex = 0;
			int  raspunsIluzie;
			int cardValue = -1;
			displayBoard(n1, n2, ok);
			if (turns == 0) {
			currentPlayer = isPlayer1Turn ? player1 : player2;
			opponent = isPlayer1Turn ? player2 : player1;
			}
			else {
				Player aux;
				aux = opponent;
				opponent = currentPlayer;
				currentPlayer = aux;
			}

			cout << "Este randul " << currentPlayer.color << (isPlayer1Turn ? "jucatorului 1" : "jucatorului 2") << RESET << endl;
			char choice;



			if (!hasUsedMagic) {
				if (currentPlayer.wizardName == "Eliminatorul" && opponent.LastPoz.i != -1) {
					std::cout << "Vrei sa folosesti puterea vrajitorului "
						<< currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::removeLastOpponentCard(currentPlayer, opponent, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}
				}
				else if (currentPlayer.wizardName == "Maestrul Eterului") {
					std::cout << "Vrei sa folosesti puterea vrajitorului "
						<< currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::addExtraEther(currentPlayer);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}
				}
				else if ((currentPlayer.wizardName == "Distrugatorul de Randuri") && (checkRowForWizz(n1, n2, ok) == 4 || checkRowForWizz(n1, n2, ok) == 3)) {
					std::cout << "Vrei sa folosesti puterea vrajitorului "
						<< currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::destroyRow(currentPlayer, n1, n2, boardSize, board);
						hasUsedMagic = true;
						ok = 0;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}
				}
				else if (currentPlayer.wizardName == "Transformatorul de Spatii") {
					std::cout << "Vrei sa folosesti puterea vrajitorului "
						<< currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::transformToAbyss(currentPlayer, n1, n2, ok, boardSize, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						turns += 1;
						if (checkRow() && checkCol()) {
							ok = 1;
						}
						continue;
					}
				}
				else if (currentPlayer.wizardName == "Muta Teancuri") {
					std::cout << "Vrei sa folosesti puterea vrajitorului " << currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::moveStack(currentPlayer, opponent, n1, n2, ok, boardSize, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}
				}
				else if (currentPlayer.wizardName == "Muta Teancuri Adversar") {
					std::cout << "Vrei sa folosesti puterea vrajitorului " << currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::moveOpponentStack(currentPlayer, opponent, n1, n2, ok, boardSize, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}

				}
				else if (currentPlayer.wizardName == "Acopera Carti") {
					std::cout << "Vrei sa folosesti puterea vrajitorului? " << currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::coverOpponentCard(currentPlayer, opponent, n1, n2, ok, boardSize, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}

				}
				else if (currentPlayer.wizardName == "Transportatorul de Randuri" && checkRowForWizz(n1, n2, ok) >= 3) {
					std::cout << "Vrei sa folosesti puterea vrajitorului " << currentPlayer.wizardName << "? (y/n): ";
					std::cin >> choice;
					if (choice == 'y') {
						Wizzard::transportRow(currentPlayer, opponent, n1, n2, ok, boardSize, board);
						hasUsedMagic = true;
						isPlayer1Turn = !isPlayer1Turn;
						continue;
					}
				
				}


			}
			if (hasUsedElements < 2) {
				cout << "Doresti sa folosesti un element? y/n\n";
				char choice4;
				cin >> choice4;
				if (choice4 == 'y') {
					cout << "Ce element doresti sa folosesti?  Elementul: " << element1 << " sau elementul: " << element2 << " ?\n";
					string elemChoice;
					cin >> elemChoice;
					if (elemChoice == "distrugere") {
						Elemente::distrugere(opponent, board);
						hasUsedElements += 1;
					}
					else if (elemChoice == "flacari") {
						Elemente::flacari(opponent, currentPlayer, board, boardSize, ok, n1, n2);
						hasUsedElements += 1;
					}
					else if (elemChoice == "lava") {
						Elemente::lava(opponent, currentPlayer, board, boardSize, n1, n2);
						hasUsedElements += 1;
					}
					else if (elemChoice == "dinCenusa") {
						Elemente::dinCenusa(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "vijelie") {
						Elemente::vijelie(currentPlayer, opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "vifor") {
						Elemente::vifor(currentPlayer, opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "scantei") {
						Elemente::scantei(currentPlayer, opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "uragan") {
						std::cout << "Vrei sa muti randul in dreapta? y/n: ";
						char ch;
						std::cin >> ch;
						if (ch == 'y') {
							Elemente::uragan(currentPlayer, opponent, board, boardSize, true);
						}
						else {
							Elemente::uragan(currentPlayer, opponent, board, boardSize, false);
						}
						hasUsedElements += 1;
					}
					else if (elemChoice == "rafala") {
						Elemente::rafala(currentPlayer, opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "miraj") {
						if (currentPlayer.ceckIluzie) {
							Elemente::miraj(currentPlayer, board, boardSize);
							hasUsedElements += 1;
						}
						else {
							std::cout << "Nu poti folosi Miraj deoarece nu ai nicio iluzie pe tabla.\n";
						}
					}
					else if (elemChoice == "furtuna") {
						Elemente::furtuna(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "maree") {
						Elemente::maree(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "ceata") {
						if (!currentPlayer.ceckIluzie) {
							Elemente::ceata(currentPlayer, board, boardSize);
							hasUsedElements += 1;
						}
						else {
							std::cout << "Nu poti avea mai mult de o iluzie simultan pe tabla.\n";
						}
					}
					else if (elemChoice == "val") {
						Elemente::val(opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "tsunami") {
						bool hasSpace = false;
						for (int i = 0; i < boardSize; ++i) {
							for (int j = 0; j < boardSize; ++j) {
								if (Functions::lastK(i, j, board) == -1) { 
									hasSpace = true;
									break;
								}
							}
							if (hasSpace) break;
						}
						if (hasSpace) {
							Elemente::tsunami(currentPlayer, opponent, board, boardSize);
							hasUsedElements += 1;
						}
						else {
							std::cout << "Nu exista spatii libere suficiente pentru a activa Tsunami.\n";
						}
					}
					else if (elemChoice == "cascade") {
						Elemente::cascade(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "sprijin") {
						Elemente::sprijin(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "cutremur") {
						Elemente::cutremur(board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "sfarimare") {
						Elemente::sfarimare(opponent, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "granite") {
						Elemente::granite(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "avalansa") {
						Elemente::avalansa(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else if (elemChoice == "bolovan") {

						if (currentPlayer.ceckIluzie) {
							Elemente::bolovan(currentPlayer, board, boardSize);
							hasUsedElements += 1;
						}
						else {
							std::cout << "Puterea Bolovan este disponibilă doar dacă se joacă jocul cu iluzii.\n";
						}
					}
					else if (elemChoice == "vartejDeApa") {
						bool valid = false;
						for (int i = 0; i < boardSize; ++i) {
							for (int j = 0; j < boardSize; ++j) {
								if (Functions::lastK(i, j, board) == -1) { 
									valid = true;
									break;
								}
							}
							if (valid) break;
						}
						if (valid) {
							Elemente::vartejDeApa(currentPlayer, board, boardSize);
							hasUsedElements += 1;
						}
						else {
							std::cout << "Mutarea nu respecta regulile pentru Vartej de apa.\n";
						}
						Elemente::vartejDeApa(currentPlayer, board, boardSize);
						hasUsedElements += 1;
					}
					else {
						std::cerr << "Element invalid ales: " << elemChoice << std::endl;
					}


				}
			}
			if (!currentPlayer.ceckIluzie) {
				cout << "Doresti sa folosesti o iluzie?   1.Da   2.Nu\n";
				cin >> raspunsIluzie;
				if (raspunsIluzie == 1) {
					selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
					iluzie(row, col, cardValue, turns, currentPlayer, cardIndex);
				}
				else {
					selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
					while (addCard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex) == 1) {
						selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
					}
				}
			}
			else {
				selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
				while (addCard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex) == 1) {
					selectCard(currentPlayer, row, col, cardIndex, turns, cardValue, ok, n1, n2);
				}
			}
			if (ok == 0) {
				if (row < n1) { n1 = row; }
				if (col > n2) { n2 = col; }
			}
			if (checkRow() && checkCol()) {
				ok = 1;
			}

			if (checkWin(currentPlayer, n1, n2, turns, ok) == 1 && ok == 1) {
				displayBoard(n1, n2, ok);
				std::cout << "Jucatorul " << (isPlayer1Turn ? "1" : "2") << " a castigat aceasta runda!\n";
				if (isPlayer1Turn) {
					player1.totalscore += 1;
				}
				else {
					player2.totalscore += 1;
				}
				std::this_thread::sleep_for(std::chrono::seconds(5));
				break;
			}
			else {
				displayBoard(n1, n2, ok);
			}
			if (check2xForExplosion(board, n1, n2,boardSize) && ok==1) {
				cout << "se poate face explozie\n";
				cout << "Doresti sa rotest matricea ? y/n\n";
				char choice1;
				cin >> choice1;
				while (choice1 == 'y') {
				EX.rotire_matrice_90(CE);
				displayBoard(n1, n2, ok);
				cout << "Doresti sa rotest matricea ? y/n\n";
				cin >> choice1;
				}
				//std::this_thread::sleep_for(std::chrono::seconds(3));
				cout << "Doresti sa folosesti exploiza? y/n\n";
				char choice2;
				cin >> choice2;
				if (choice2 == 'y') {
					executie_CE(player1, player2, CE, n1, n2);
					std::ranges::sort(player1.cards);
					std::ranges::sort(player2.cards);
				}
			}

			isPlayer1Turn = !isPlayer1Turn;
		}
		if (player1.totalscore == 2) {
			std::cout << "Jucatorul 1 a castigat best of 3!\n";
		}
		else {
			std::cout << "Jucatorul 2 a castigat best of 3!\n";
		}
	}
}

void Game::translatie_CE(std::vector<locatie_efect>& CE, int n1, int n2,int  boardsize)
{
	if (boardsize == 5)
	{
		for (int i = 0; i < CE.size(); i++)
		{
			CE[i].x += n1;
			CE[i].y += n2 - 2;
		}
	}
	else
		if(boardsize == 7)
	{
		for (int i = 0; i < CE.size(); i++)
		{
			CE[i].x += n1;
			CE[i].y += n2 - 3;
		}
	}
	


}

void Game::returnCard(Player& player1, Player& player2, int x, int y)
{

	if (player1.symbol = 'A')

	{
		if (board[x][y][lastK(x, y)] < 0)
		{
			player2.score -= abs(board[x][y][lastK(x, y)]);
			player2.cards.push_back(abs(board[x][y][lastK(x, y)]));
			board[x][y][lastK(x, y)] = 0;
		}

		else


			if (board[x][y][lastK(x, y)] > 0)
			{
				player1.score -= abs(board[x][y][lastK(x, y)]);
				player1.cards.push_back(abs(board[x][y][lastK(x, y)]));
				board[x][y][lastK(x, y)] = 0;
			}

	}

	else

		if (player1.symbol = 'B')

		{
			if (board[x][y][lastK(x, y)] > 0)
			{
				player2.score -= abs(board[x][y][lastK(x, y)]);
				player2.cards.push_back(abs(board[x][y][lastK(x, y)]));
				board[x][y][lastK(x, y)] = 0;
			}

			else

				if (board[x][y][lastK(x, y)] < 0)
				{
					player1.score -= abs(board[x][y][lastK(x, y)]);
					player1.cards.push_back(abs(board[x][y][lastK(x, y)]));
					board[x][y][lastK(x, y)] = 0;
				}

		}
}

void Game::removeCard(Player& player1, Player& player2, int x, int y) {

	if (board[x][y][lastK(x, y)] < 0)
	{
	player2.score -= abs(board[x][y][lastK(x, y)]);
	board[x][y][lastK(x, y)] = 0;
	}

	else

		if (board[x][y][lastK(x, y)] > 0)
	{
		player1.score -= abs(board[x][y][lastK(x, y)]);
		board[x][y][lastK(x, y)] = 0;
	}
}

void Game::executie_CE( Player& currentPlayer, Player& opponent, vector<locatie_efect> CE, int n1, int n2)
{
	translatie_CE(CE, n1, n2, boardSize);

	for (int i = 0; i < CE.size(); i++)
	{
		switch (CE[i].tip_efect)
		{
		case 1:

			removeCard(currentPlayer, opponent, CE[i].x, CE[i].y);
			break;

		case 2:

			returnCard(currentPlayer,opponent, CE[i].x, CE[i].y);
			break;

		case 3:
			
			for (int k = lastK(CE[i].x, CE[i].y); k >= 0; k--) {
				board[CE[i].x][CE[i].y][k] = 0;
			}
			
			board[CE[i].x][CE[i].y][0] = 15;
			break;

		}
	}
}




