#include "Functions.h"
#include "Game.h"
#include <vector>
 
int Functions::lastK(int i, int j, std::vector<std::vector<std::vector<int>>>& board)
{
	int k = 0;
	while (board[i][j][k] != 0) { k++; };
	if (k == 0) { return  k; }
	return  k -= 1;

}

void Functions::translatatePozFor3x3(int& row, int& col, int n1, int n2)
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

void Functions::translatatePozFor4x4(int& row, int& col, int n1, int n2)
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

bool Functions::checkRow(int boardSize, std::vector<std::vector<std::vector<int>>>& board)
{
		int row = 0;

		for (int i = 0; i < boardSize; i++) {
			bool hasNonZero = false;
			for (int j = 0; j < boardSize; j++) {
				if (board[i][j][lastK(i, j, board)] != 0) {
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

bool Functions::checkCol(int boardSize, std::vector<std::vector<std::vector<int>>>& board)
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

void Functions::returnCard(Player& currentPlayer, Player& opponent, int x, int y, std::vector<std::vector<std::vector<int>>>& board)
{
	if (board[x][y][lastK(x, y,board)] < 0)
	{
		opponent.score -= abs(board[x][y][lastK(x, y, board)]);
		opponent.cards.push_back(abs(board[x][y][lastK(x, y, board)]));
		board[x][y][lastK(x, y, board)] = 0;
	}

	else

		if (board[x][y][lastK(x, y, board)] > 0)
		{
			currentPlayer.score -= abs(board[x][y][lastK(x, y, board)]);
			currentPlayer.cards.push_back(abs(board[x][y][lastK(x, y, board)]));
			board[x][y][lastK(x, y, board)] = 0;
		}

}

void Functions::removeCard(Player& currentPlayer, Player& opponent, int x, int y, std::vector<std::vector<std::vector<int>>>& board)
{
	if (board[x][y][lastK(x, y, board)] < 0)
	{
		opponent.score -= abs(board[x][y][lastK(x, y, board)]);
	
		board[x][y][lastK(x, y, board)] = 0;
	}

	else

		if (board[x][y][lastK(x, y, board)] > 0)
		{
			currentPlayer.score -= abs(board[x][y][lastK(x, y, board)]);
			
			board[x][y][lastK(x, y, board)] = 0;
		}
}

void Functions::printCenteredforBoard(const std::string& text, int ok, int boardSize)
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




