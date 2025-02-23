#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

Game::Game(int size) : boardSize(size) {

	board = std::vector<std::vector<std::vector<int>>>(size, std::vector<std::vector<int>>(size, std::vector<int>(4, 0)));

	std::srand(static_cast<unsigned int>(std::time(0)));

	player1.color = BLUE;
	player1.symbol = 'A';

	player2.color = RED;
	player2.symbol = 'B';

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
	currentPlayer.ceckIluzie = true;
}

void Game::displayBoard(int n1, int n2, int ok) {
	system("cls");
	player1.color = BLUE;
	player2.color = RED;
	printCentered("Jucatorul 1", "left");
	printCentered("Jucatorul 2", "right");
	cout << endl;
	if (currentPlayer.wizardName == "Eliminatorul") {
		printCentered("are vrajitorul Eliminatorul: ", "left");
	}
	else if (currentPlayer.wizardName == "Maestrul Eterului") {
		printCentered("are vrajitorul: Maestrul Eterului", "left");
	}
	else if (currentPlayer.wizardName == "Distrugatorul de Randuri") {
		printCentered("are vrajitorul: Distrugatorul de Randuri", "left");
	}
	else if (currentPlayer.wizardName == "Transformatorul de Spatii") {
		printCentered("are vrajitorul: Transformatorul de Spatii", "left");
	}
	else if (currentPlayer.wizardName == "Muta Teancuri") {
		printCentered("are vrajitorul: Muta Teancuri", "left");
	}
	else if (currentPlayer.wizardName == "Muta Teancuri Adversar") {
		printCentered("are vrajitorul: Muta Teancuri Adversar", "left");
	}
	else if (currentPlayer.wizardName == "Acopera Carti") {
		printCentered("are vrajitorul: Acopera Carti", "left");
	}
	else if (currentPlayer.wizardName == "Transportatorul de Randuri") {
		printCentered("are vrajitorul: Transportatorul de Randuri", "left");
	}

	if (opponent.wizardName == "Eliminatorul") {
		printCentered("are vrajitorul Eliminatorul: ", "right");
	}
	else if (opponent.wizardName == "Maestrul Eterului") {
		printCentered("are vrajitorul: Maestrul Eterului", "right");
	}
	else if (opponent.wizardName == "Distrugatorul de Randuri") {
		printCentered("are vrajitorul: Distrugatorul de Randuri", "right");
	}
	else if (opponent.wizardName == "Transformatorul de Spatii") {
		printCentered("are vrajitorul: Transformatorul de Spatii", "right");
	}
	else if (opponent.wizardName == "Muta Teancuri") {
		printCentered("are vrajitorul: Muta Teancuri", "right");
	}
	else if (opponent.wizardName == "Muta Teancuri Adversar") {
		printCentered("are vrajitorul: Muta Teancuri Adversar", "right");
	}
	else if (opponent.wizardName == "Acopera Carti") {
		printCentered("are vrajitorul: Acopera Carti", "right");
	}
	else if (opponent.wizardName == "Transportatorul de Randuri") {
		printCentered("are vrajitorul: Transportatorul de Randuri", "right");
	}
	cout << endl;
	printCentered(" carti: ", "left");
	std::string cards1;
	for (int card : currentPlayer.cards) {
		if (card == 9) {
			cards1 += "E ";
		}
		else {
			cards1 += std::to_string(card) + " ";
		}
	}
	cout << player1.color;
	printCentered(cards1, "left");
	cout << RESET;
	cards1 = "";
	printCentered(" carti: ", "right");
	std::string cards2;
	for (int card : opponent.cards) {
		if (card == 9) {
			cards2 += "E ";
		}
		else {
			cards2 += std::to_string(card) + " ";
		}
	}
	cout << player2.color;
	printCentered(cards2, "right");
	cout << RESET;
	printCentered("Tabla de joc : ", "center"); cout << "\n\n\n";
	if (boardSize == 5) {
		int i;
		for ((ok == 1 ? i = n1 : i = 0); (ok == 1 ? i < n1 + 3 : i < boardSize); i++) {
			for (int j = n2 - 2; j <= n2; j++) {
				if (board[i][j][0] == 0) {
					if (j == n2 - 2) {
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
					if (j == n2 - 2) {
						printCenteredforBoard(" ", ok);
					}
					int k = lastK(i, j);
					int cellValue = board[i][j][k];
					switch (cellValue) {
					case 9:
						cout << player1.color << "[E]" << RESET;
						break;
					case -9:
						cout << player2.color << "[E]" << RESET;
						break;
					case 11:
						cout << player1.color << "[#]" << RESET;
						break;
					case -11:
						cout << player2.color << "[#]" << RESET;
						break;
					case 15:
						cout << player1.color << "[@]" << RESET;
						break;
					case -15:
						cout << player2.color << "[@]" << RESET;
						break;
					default:
						if (cellValue > 0) {
							cout << player1.color << "[" << cellValue << "]" << RESET;
						}
						else {
							cout << player2.color << "[" << -cellValue << "]" << RESET;
						}
						break;
					}

				}
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		int i;
		for ((ok == 1 ? i = n1 : i = 0); (ok == 1 ? i < n1 + 4 : i < boardSize); i++) {
			for (int j = n2 - 3; j <= n2; j++) {
				if (board[i][j][0] == 0) {
					if (j == n2 - 2) {
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
					if (j == n2 - 2) {
						printCenteredforBoard(" ", ok);
					}
					int k = lastK(i, j);
					int cellValue = board[i][j][k];
					switch (cellValue) {
					case 9:
						cout << player1.color << "[E] " << RESET;
						break;
					case -9:
						cout << player2.color << "[E] " << RESET;
						break;
					case 11:
						cout << player1.color << "[#] " << RESET;
						break;
					case -11:
						cout << player2.color << "[#] " << RESET;
						break;
					case 15:
						cout << player1.color << "[@]" << RESET;
						break;
					case -15:
						cout << player2.color << "[@]" << RESET;
						break;
					default:
						if (cellValue > 0) {
							cout << player1.color << "[" << cellValue << "] " << RESET;
						}
						else {
							cout << player2.color << "[" << -cellValue << "] " << RESET;
						}
						break;
					}

				}
			}
			cout << endl;
		}
		cout << endl;
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
			displayBoard(n1, n2, ok);
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
				return true;
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
				return true;
			}
		}


		if (turns == 4 * 4 && ok == 1) {
			displayBoard(n1, n2, ok);
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

void Game::selectCard(Player& currentPlayer, int& row, int& col, int& cardIndex, int turns, int& cardValue)
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
		selectCard(currentPlayer, row, col, cardIndex, turns, cardValue);
	}
	else if (turns != 0) {
		cout << "Alegeti pozitia (linie si coloana): ";
		cin >> row >> col;
	}
	else {
		row = 2;
		col = 2;
		if (boardSize == 7) {
			row = 3, col = 3;
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

	//isPlayer1Turn = !isPlayer1Turn;
}




void Game::playGame() {
	int turns = 0;
	int n1, n2;
	int ok = 0;
	addSize(n1, n2);
	while (true) {
		int row, col, cardIndex = 0;
		int  raspunsIluzie;
		int cardValue = -1;
		if (turns != 0) {
			displayBoard(n1, n2, ok);
		}

		currentPlayer = isPlayer1Turn ? player1 : player2;
		opponent = isPlayer1Turn ? player2 : player1;
		cout << "Este randul " << (isPlayer1Turn ? player1.color : player2.color) << (isPlayer1Turn ? "jucatorului 1" : "jucatorului 2") << RESET << endl;
		char choice;



		if (!currentPlayer.hasUsedMagic) {
			if (currentPlayer.wizardName == "Eliminatorul" && opponent.LastPoz.i != -1) {
				std::cout << "Vrei sa folosesti puterea vrajitorului "
					<< currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					removeLastOpponentCard(currentPlayer, opponent);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}
			}
			else if (currentPlayer.wizardName == "Maestrul Eterului") {
				std::cout << "Vrei sa folosesti puterea vrajitorului "
					<< currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					addExtraEther(currentPlayer);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}
			}
			else if ((currentPlayer.wizardName == "Distrugatorul de Randuri") && (checkRowForWizz(n1, n2, ok) == 4 || checkRowForWizz(n1, n2, ok) == 3)) {
				std::cout << "Vrei sa folosesti puterea vrajitorului "
					<< currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					destroyRow(currentPlayer, n1, n2);
					currentPlayer.hasUsedMagic = true;
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
					transformToAbyss(currentPlayer, n1, n2, ok);
					currentPlayer.hasUsedMagic = true;
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
					moveStack(currentPlayer, opponent, n1, n2, ok);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}
			}
			else if (currentPlayer.wizardName == "Muta Teancuri Adversar") {
				std::cout << "Vrei sa folosesti puterea vrajitorului " << currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					moveOpponentStack(currentPlayer, opponent, n1, n2, ok);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}

			}
			else if (currentPlayer.wizardName == "Acopera Carti") {
				std::cout << "Vrei sa folosesti puterea vrajitorului? " << currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					coverOpponentCard(currentPlayer, opponent, n1, n2, ok);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}

			}
			else if (currentPlayer.wizardName == "Transportatorul de Randuri" && checkRowForWizz(n1, n2, ok) == 3) {
				std::cout << "Vrei sa folosesti puterea vrajitorului " << currentPlayer.wizardName << "? (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					transportRow(currentPlayer, opponent, n1, n2, ok);
					currentPlayer.hasUsedMagic = true;
					isPlayer1Turn = !isPlayer1Turn;
					continue;
				}

			}


		}

		if (!currentPlayer.ceckIluzie) {
			cout << "Doresti sa folosesti o iluzie? \n 1.Da   2.Nu\n";
			cin >> raspunsIluzie;
			if (raspunsIluzie == 1) {
				selectCard(currentPlayer, row, col, cardIndex, turns, cardValue);
				if (ok == 1) {
					if (boardSize == 5) {
						translatatePozFor3x3(row, col, n1, n2);
					}
					else if (boardSize == 7) {
						translatatePozFor4x4(row, col, n1, n2);
					}
				}
				if (ok == 0) {
					if (row < n1) { n1 = row; }
					if (col > n2) { n2 = col; }
				}
				iluzie(row, col, cardValue, turns, currentPlayer, cardIndex);
				isPlayer1Turn = !isPlayer1Turn;
				turns += 1;
				continue;
			}
		}


		selectCard(currentPlayer, row, col, cardIndex, turns, cardValue);
		if (ok == 1) {
			if (boardSize == 5) {
				translatatePozFor3x3(row, col, n1, n2);
			}
			if (boardSize == 7) {
				translatatePozFor4x4(row, col, n1, n2);
			}
		}

		if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || cardIndex < 0 || cardIndex >= currentPlayer.cards.size()) {
			cout << "Pozitie invalida. Incercati din nou.\n";
			continue;
		}

		if (turns > 0 && !isAdjacent(row, col)) {
			cout << "Trebuie sa plasati cartea in apropierea unei alte carti deja plasate. Incercati din nou.\n";
			continue;
		}


		if ((board[row][col][lastK(row, col)] == 0 || abs(board[row][col][lastK(row, col)]) < cardValue) && abs(board[row][col][lastK(row, col)]) != 9) {
			addCardOnBoard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex);
			currentPlayer.LastPoz.i = row;
			currentPlayer.LastPoz.j = col;
			currentPlayer.LastPoz.k = lastK(row, col);

		}
		else if (abs(board[row][col][lastK(row, col)]) == 9) {
			if (cardValue == 9 && board[row][col][lastK(row, col)] == 0) {
				addCardOnBoard(row, col, opponent, currentPlayer, cardValue, turns, cardIndex);
				currentPlayer.LastPoz.i = row;
				currentPlayer.LastPoz.j = col;
				currentPlayer.LastPoz.k = lastK(row, col);
				continue;
			}
			else if (cardValue == 9 && board[row][col][lastK(row, col)] != 0) {
				cout << "Nu se poate plasa cartea. Incercati din nou.\n";
				continue;
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
			}
			else {
				cout << "Cartea " << (isPlayer1Turn ? player1.color : player2.color) << (isPlayer1Turn ? "jucatorului 1" : "jucatorului 2") << RESET << " este mai mica decat cartea de sub iluzie\n";
				currentPlayer.cards.erase(currentPlayer.cards.begin() + cardIndex);
				isPlayer1Turn = !isPlayer1Turn;
				continue;
			}
			continue;

		}
		else {
			cout << "Nu se poate plasa cartea. Incercati din nou.\n";
			continue;
		}
		if (ok == 0) {
			if (row < n1) { n1 = row; }
			if (col > n2) { n2 = col; }
		}
		if (checkRow() && !checkCol()) {
			if (row<n1 || row>n1 + 2) {
				cout << "Numarul de randuri a maxim a fost atins, trebuie sa plasezi cartea pe randurile deja existente\n";
				continue;
			}
		}
		if (!checkRow() && checkCol()) {
			if (col<n2 - 2 || col > n2) {
				cout << "Numarul de coloane a maxim a fost atins, trebuie sa plasezi cartea pe coloanele deja existente\n";
				continue;
			}
		}
		if (checkRow() && checkCol()) {
			ok = 1;
		}

		if (checkWin(currentPlayer, n1, n2, turns, ok) == 1 && ok == 1) {
			displayBoard(n1, n2, ok);
			cout << "Jucatorul " << (isPlayer1Turn ? "1" : "2") << " a castigat prin aliniere!\n";
			break;
		}


		isPlayer1Turn = !isPlayer1Turn;
	}
}

void Game::addExtraEther(Player& player) {
	if (player.hasUsedMagic) {
		std::cout << "Puterea vrajitorului " << player.wizardName << " a fost deja folosita!\n";
		return;
	}

	player.cards.push_back(9);
	player.hasUsedMagic = true;

	std::cout << "Vrajitorul " << player.wizardName
		<< " a adaugat o carte Eter in mana jucatorului!\n";
}
void Game::removeLastOpponentCard(Player& currentPlayer, Player& opponent) {

	opponent.score -= abs(board[opponent.LastPoz.i][opponent.LastPoz.j][opponent.LastPoz.k]);
	board[opponent.LastPoz.i][opponent.LastPoz.j][opponent.LastPoz.k] = 0;
	std::cout << "Vrajitorul a eliminat ultima carte a adversarului de la pozitia ("
		<< opponent.LastPoz.i << ", " << opponent.LastPoz.j << ").\n";

}
void Game::destroyRow(Player& player, int n1, int n2) {
	std::cout << "Alege un rand pentru a-l distruge (0 - " << (boardSize == 5 ? n1 + 1 : n1 + 2) << "): ";
	int row, col;
	std::cin >> row;
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
	int size = boardSize == 5 ? n1 + 2 : n1 + 3;
	if (row < n1 || row > size) {
		std::cout << "Rand invalid! Operatiunea a fost anulata.\n";
		return;
	}

	bool hasPlayerCard = false;
	if (boardSize == 5) {
		col = n2 - 2;

	}
	else if (boardSize == 7) {
		col = n2 - 3;

	}
	else { col = 0; }
	for (col; col <= n2; ++col) {
		if (board[row][col][0] != 0 && (board[row][col][0] > 0 && player.symbol == 'A') ||
			(board[row][col][0] < 0 && player.symbol == 'B')) {
			hasPlayerCard = true;
			break;
		}
	}

	if (!hasPlayerCard) {
		std::cout << "Nu exista nicio carte vizibila a ta pe randul ales. Operatiunea a fost anulata.\n";
		return;
	}
	if (boardSize == 5) {
		col = n2 - 2;

	}
	else if (boardSize == 7) {
		col = n2 - 3;

	}

	for (col; col < n2; ++col) {
		for (int k = 0; k < 4; ++k) {
			board[row][col][k] = 0;
		}
	}

	std::cout << "Vrajitorul tau a distrus randul " << row << "!\n";
	player.hasUsedMagic = true;
}
void Game::transformToAbyss(Player& player, int& n1, int& n2, int& ok) {
	std::cout << "Alege o pozitie (linie si coloana) pentru a o transforma intr-o groapa: ";
	int row, col;
	std::cin >> row >> col;
	if (boardSize == 5 && ok == 1) {
		translatatePozFor3x3(row, col, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		translatatePozFor4x4(row, col, n1, n2);
	}
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col][0] != 0) {
		std::cout << "Pozitie invalida sau ocupata! Operatiunea a fost anulata.\n";
		return;
	}
	if (ok == 0) {
		if (row < n1) { n1 = row; }
		if (col > n2) { n2 = col; }
		cout << "n1= " << n1 << "  n2= " << n2 << "\n";
	}
	bool isWorking = false;
	while (!isWorking) {
		if (checkRow() && !checkCol()) {
			if (row<n1 || row>n1 + 2) {
				cout << "Numarul de randuri a maxim a fost atins, trebuie sa plasezi cartea pe randurile deja existente\n";
				std::cout << "Alege o pozitie (linie si coloana) pentru a o transforma intr-o groapa: ";
				std::cin >> row >> col;
			}
		}
		if (!checkRow() && checkCol()) {
			if (col<n2 - 2 || col > n2) {
				cout << "Numarul de coloane a maxim a fost atins, trebuie sa plasezi cartea pe coloanele deja existente\n";
				std::cout << "Alege o pozitie (linie si coloana) pentru a o transforma intr-o groapa: ";
				std::cin >> row >> col;
			}
		}
		if (ok == 0) {
			if (row < n1) { n1 = row; }
			if (col > n2) { n2 = col; }
			cout << "n1= " << n1 << "  n2= " << n2 << "\n";
		}
		if (checkRow() && checkCol()) {
			ok = 1;
			isWorking = true;
		}
		else {
			isWorking = true;
		}

	}

	if (player.symbol == 'A') {
		board[row][col][0] = 15;
	}
	else {
		board[row][col][0] = -15;
	}
	std::cout << "Vrajitorul tau a transformat pozitia (" << row << ", " << col << ") intr-o groapa!\n";
	player.hasUsedMagic = true;
}

void Game::moveStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int fromRow, fromCol, toRow, toCol;
	std::cout << "Alege coordonatele teancului de mutat (linie coloana): ";
	std::cin >> fromRow >> fromCol;
	if (boardSize == 5 && ok == 1) {
		translatatePozFor3x3(fromRow, fromCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		translatatePozFor4x4(fromRow, fromCol, n1, n2);
	}
	if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize || board[fromRow][fromCol][0] == 0) {
		std::cout << "Pozitie invalida sau goala! Operatiunea a fost anulata.\n";
		return;
	}


	int topCard = board[fromRow][fromCol][lastK(fromRow, fromCol)];
	if ((currentPlayer.symbol == 'A' && topCard < 0) || (currentPlayer.symbol == 'B' && topCard > 0)) {
		std::cout << "Nu poti muta acest teanc deoarece nu detii cartea de deasupra!\n";
		return;
	}

	std::cout << "Alege coordonatele pozitiei goale unde doresti sa muti teancul (linie coloana): ";
	std::cin >> toRow >> toCol;
	if (boardSize == 5 && ok == 1) {
		translatatePozFor3x3(toRow, toCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		translatatePozFor4x4(toRow, toCol, n1, n2);
	}
	if (toRow < 0 || toRow >= boardSize || toCol < 0 || toCol >= boardSize || board[toRow][toCol][0] != 0) {
		std::cout << "Pozitia tinta este invalida sau ocupata! Operatiunea a fost anulata.\n";
		return;
	}
	int k = 0;
	while (board[fromRow][fromCol][k] != 0) {
		board[toRow][toCol][k] = board[fromRow][fromCol][k];
		board[fromRow][fromCol][k] = 0;
		k++;
	}
	if (opponent.LastPoz.i == fromRow && opponent.LastPoz.j == fromCol) {
		opponent.LastPoz.i = toRow;
		opponent.LastPoz.j = toCol;
	}
	if (currentPlayer.LastPoz.i == fromRow && currentPlayer.LastPoz.j == fromCol) {
		currentPlayer.LastPoz.i = toRow;
		currentPlayer.LastPoz.j = toCol;
	}

	std::cout << "Teancul a fost mutat cu succes de la (" << fromRow << ", " << fromCol << ") la (" << toRow << ", " << toCol << ").\n";

	currentPlayer.hasUsedMagic = true;
}
void Game::moveOpponentStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int fromRow, fromCol, toRow, toCol;
	std::cout << "Alege coordonatele teancului adversarului de mutat (linie coloana): ";
	std::cin >> fromRow >> fromCol;
	if (boardSize == 5 && ok == 1) {
		translatatePozFor3x3(fromRow, fromCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		translatatePozFor4x4(fromRow, fromCol, n1, n2);
	}
	if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize || board[fromRow][fromCol][0] == 0) {
		std::cout << "Pozitie invalida sau goala! Operatiunea a fost anulata.\n";
		return;
	}


	int topCard = board[fromRow][fromCol][lastK(fromRow, fromCol)];
	if ((opponent.symbol == 'A' && topCard < 0) || (opponent.symbol == 'B' && topCard > 0)) {
		std::cout << "Nu poti muta acest teanc deoarece adversarul nu detine cartea de deasupra!\n";
		return;
	}

	std::cout << "Alege coordonatele pozitiei goale unde doresti sa muti teancul (linie coloana): ";
	std::cin >> toRow >> toCol;
	if (toRow < 0 || toRow >= boardSize || toCol < 0 || toCol >= boardSize || board[toRow][toCol][0] != 0) {
		std::cout << "Pozitia tinta este invalida sau ocupata! Operatiunea a fost anulata.\n";
		return;
	}


	int k = 0;
	while (board[fromRow][fromCol][k] != 0) {
		board[toRow][toCol][k] = board[fromRow][fromCol][k];
		board[fromRow][fromCol][k] = 0;
		k++;
	}

	if (opponent.LastPoz.i == fromRow && opponent.LastPoz.j == fromCol) {
		opponent.LastPoz.i = toRow;
		opponent.LastPoz.j = toCol;
	}
	if (currentPlayer.LastPoz.i == fromRow && currentPlayer.LastPoz.j == fromCol) {
		currentPlayer.LastPoz.i = toRow;
		currentPlayer.LastPoz.j = toCol;
	}
	std::cout << "Teancul adversarului a fost mutat cu succes de la (" << fromRow << ", " << fromCol << ") la (" << toRow << ", " << toCol << ").\n";

	currentPlayer.hasUsedMagic = true;
}
void Game::coverOpponentCard(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int row, col;
	std::cout << "Alege coordonatele cartii adversarului pe care doresti sa o acoperi (linie coloana): ";
	std::cin >> row >> col;
	if (boardSize == 5 && ok == 1) {
		translatatePozFor3x3(row, col, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		translatatePozFor4x4(row, col, n1, n2);
	}
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
		std::cout << "Pozitie invalida! Operatiunea a fost anulata.\n";
		return;
	}

	int topCard = board[row][col][lastK(row, col)];
	if ((opponent.symbol == 'A' && topCard <= 0) || (opponent.symbol == 'B' && topCard >= 0)) {
		std::cout << "Pozitia selectata nu contine o carte vizibila a adversarului! Operatiunea a fost anulata.\n";
		return;
	}

	int selectedCard;
	std::cout << "Alege o carte din mana ta de valoare STRICT mai mica decat valoarea cartii adversarului (" << abs(topCard) << "): ";
	std::cin >> selectedCard;


	auto it = std::find(currentPlayer.cards.begin(), currentPlayer.cards.end(), selectedCard);
	if (it == currentPlayer.cards.end() || selectedCard >= abs(topCard)) {
		std::cout << "Carte invalida sau valoarea nu este mai mica! Operatiunea a fost anulata.\n";
		return;
	}


	board[row][col][lastK(row, col) + 1] = (currentPlayer.symbol == 'A') ? selectedCard : -selectedCard;
	currentPlayer.cards.erase(it);

	std::cout << "Cartea adversarului a fost acoperita cu succes!\n";
	currentPlayer.LastPoz.i = row;
	currentPlayer.LastPoz.j = col;
	currentPlayer.LastPoz.k = lastK(row, col);

	currentPlayer.hasUsedMagic = true;
}
void Game::transportRow(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int row, targetRow;
	std::cout << "Alege randul de pe marginea tablei pe care doresti sa il muti (linie): ";
	std::cin >> row;
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
	int maxRow = n1 + 2;
	if (boardSize == 7) {
		maxRow += 1;
	}
	if (row != n1 && row != maxRow) {
		std::cout << "Doar randurile de pe marginea tablei pot fi mutate! Operatiunea a fost anulata.\n";
		return;
	}

	std::cout << "Alege marginea pe care doresti sa muti randul selectat (0 pentru prima margine, " << maxRow << " pentru ultima): ";
	std::cin >> targetRow;
	if (boardSize == 5) {
		switch (targetRow) {
		case 0:targetRow = n1;
			break;
		case 1:targetRow = n1 + 1;
			break;
		case 2:targetRow = n1 + 2;
			break;
		}
	}
	else if (boardSize == 7) {
		switch (targetRow) {
		case 0:targetRow = n1;
			break;
		case 1:targetRow = n1 + 1;
			break;
		case 2:targetRow = n1 + 2;
			break;
		case 3:targetRow + n1 + 3;
			break;
		}
	}

	if (targetRow != n1 && targetRow != maxRow) {
		std::cout << "Marginea tinta trebuie sa fie prima sau ultima! Operatiunea a fost anulata.\n";
		return;
	}

	if (row == targetRow) {
		std::cout << "Randul selectat este deja pe marginea tinta! Operatiunea a fost anulata.\n";
		return;
	}

	for (int col = 0; col < boardSize; ++col) {
		for (int k = 0; k < 4; ++k) {
			board[targetRow][col][k] = board[row][col][k];
			board[row][col][k] = 0;
		}
	}
	if (opponent.LastPoz.i == row) {
		opponent.LastPoz.i = targetRow;
	}
	if (currentPlayer.LastPoz.i == row) {
		currentPlayer.LastPoz.i = targetRow;
	}

	std::cout << "Randul " << row << " a fost mutat pe marginea " << targetRow << " cu succes!\n";

	currentPlayer.hasUsedMagic = true;
}



