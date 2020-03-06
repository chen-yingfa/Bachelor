#include <iostream>
#include <iomanip>
#include "chessBoard.h"
using namespace std;

void ChessBoard::show() {
	cout << "   ";
	for (int i = 0; i < numRows; i++)
		cout << setw(3) << i + 1;
	cout << endl;
	
	for (int i = 0; i < numRows; i++) {
		cout << setw(3) << i + 1;
		for (int j = 0; j < numCols; j++) {
			cout << " " << board[i][j] << " ";
		}
		cout << endl;
	}
}

ChessBoard::ChessBoard(int m, int n){
	numRows = m;
	numCols = n;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			board[i][j] = '+';
		}
	}
}

bool ChessBoard::isOccupied(int x, int y) {
	if (board[x-1][y-1] == '+') return false;
	return true;
}

void ChessBoard::setPiece(int x, int y, char piece) {
	board[x-1][y-1] = piece;
}
