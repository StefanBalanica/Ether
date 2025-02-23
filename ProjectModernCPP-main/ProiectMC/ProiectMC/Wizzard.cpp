#pragma once
#include "Wizzard.h"
#include <iostream>
#include <vector>
#include "Functions.h"
using namespace std;

void Wizzard::addExtraEther(Player& player) {
	if (player.hasUsedMagic) {
		std::cout << "Puterea vrajitorului " << player.wizardName << " a fost deja folosita!\n";
		return;
	}

	player.cards.push_back(9);
	player.hasUsedMagic = true;

	std::cout << "Vrajitorul " << player.wizardName
		<< " a adaugat o carte Eter in mana jucatorului!\n";
}
 void Wizzard::removeLastOpponentCard(Player& currentPlayer, Player& opponent, std::vector<std::vector<std::vector<int>>>& board) {

	opponent.score -= abs(board[opponent.LastPoz.i][opponent.LastPoz.j][opponent.LastPoz.k]);
	board[opponent.LastPoz.i][opponent.LastPoz.j][opponent.LastPoz.k] = 0;
	std::cout << "Vrajitorul a eliminat ultima carte a adversarului de la pozitia ("
		<< opponent.LastPoz.i << ", " << opponent.LastPoz.j << ").\n";

}
void Wizzard::destroyRow(Player& player, int n1, int n2, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
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
void Wizzard::transformToAbyss(Player& player, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
	std::cout << "Alege o pozitie (linie si coloana) pentru a o transforma intr-o groapa: ";
	int row, col;
	std::cin >> row >> col;
	if (boardSize == 5 && ok == 1) {
		Functions::translatatePozFor3x3(row, col, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		Functions::translatatePozFor4x4(row, col, n1, n2);
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
		if (Functions::checkRow(boardSize,board) && !Functions::checkCol(boardSize, board)) {
			if (row<n1 || row>n1 + 2) {
				cout << "Numarul de randuri a maxim a fost atins, trebuie sa plasezi cartea pe randurile deja existente\n";
				std::cout << "Alege o pozitie (linie si coloana) pentru a o transforma intr-o groapa: ";
				std::cin >> row >> col;
			}
		}
		if (Functions::checkRow(boardSize, board) && Functions::checkCol(boardSize, board)) {
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
		if (Functions::checkRow(boardSize, board) && Functions::checkCol(boardSize, board)) {
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
void Wizzard::moveStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int fromRow, fromCol, toRow, toCol;
	std::cout << "Alege coordonatele teancului de mutat (linie coloana): ";
	std::cin >> fromRow >> fromCol;
	if (boardSize == 5 && ok == 1) {
		Functions::translatatePozFor3x3(fromRow, fromCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		Functions::translatatePozFor4x4(fromRow, fromCol, n1, n2);
	}
	if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize || board[fromRow][fromCol][0] == 0) {
		std::cout << "Pozitie invalida sau goala! Operatiunea a fost anulata.\n";
		return;
	}


	int topCard = board[fromRow][fromCol][Functions::lastK(fromRow, fromCol, board)];
	if ((currentPlayer.symbol == 'A' && topCard < 0) || (currentPlayer.symbol == 'B' && topCard > 0)) {
		std::cout << "Nu poti muta acest teanc deoarece nu detii cartea de deasupra!\n";
		return;
	}

	std::cout << "Alege coordonatele pozitiei goale unde doresti sa muti teancul (linie coloana): ";
	std::cin >> toRow >> toCol;
	if (boardSize == 5 && ok == 1) {
		Functions::translatatePozFor3x3(toRow, toCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		Functions::translatatePozFor4x4(toRow, toCol, n1, n2);
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
void Wizzard::moveOpponentStack(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int fromRow, fromCol, toRow, toCol;
	std::cout << "Alege coordonatele teancului adversarului de mutat (linie coloana): ";
	std::cin >> fromRow >> fromCol;
	if (boardSize == 5 && ok == 1) {
		Functions::translatatePozFor3x3(fromRow, fromCol, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		Functions::translatatePozFor4x4(fromRow, fromCol, n1, n2);
	}
	if (fromRow < 0 || fromRow >= boardSize || fromCol < 0 || fromCol >= boardSize || board[fromRow][fromCol][0] == 0) {
		std::cout << "Pozitie invalida sau goala! Operatiunea a fost anulata.\n";
		return;
	}


	int topCard = board[fromRow][fromCol][Functions::lastK(fromRow, fromCol, board)];
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
void Wizzard::coverOpponentCard(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
	if (currentPlayer.hasUsedMagic) {
		std::cout << "Puterea vrajitorului a fost deja folosita!\n";
		return;
	}

	int row, col;
	std::cout << "Alege coordonatele cartii adversarului pe care doresti sa o acoperi (linie coloana): ";
	std::cin >> row >> col;
	if (boardSize == 5 && ok == 1) {
		Functions::translatatePozFor3x3(row, col, n1, n2);
	}
	else if (boardSize == 7 && ok == 1) {
		Functions::translatatePozFor4x4(row, col, n1, n2);
	}
	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
		std::cout << "Pozitie invalida! Operatiunea a fost anulata.\n";
		return;
	}

	int topCard = board[row][col][Functions::lastK(row, col, board)];
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


	board[row][col][Functions::lastK(row, col, board) + 1] = (currentPlayer.symbol == 'A') ? selectedCard : -selectedCard;
	currentPlayer.cards.erase(it);

	std::cout << "Cartea adversarului a fost acoperita cu succes!\n";
	currentPlayer.LastPoz.i = row;
	currentPlayer.LastPoz.j = col;
	currentPlayer.LastPoz.k = Functions::lastK(row, col, board);

	currentPlayer.hasUsedMagic = true;
}
void Wizzard::transportRow(Player& currentPlayer, Player& opponent, int& n1, int& n2, int& ok, int boardSize, std::vector<std::vector<std::vector<int>>>& board) {
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