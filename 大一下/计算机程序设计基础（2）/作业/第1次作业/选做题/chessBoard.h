using namespace std;

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

class ChessBoard {
private:
	char board[30][30];
	int numRows = 15, numCols = 15;
	
public:
	ChessBoard(int m, int n);
	void show();
	bool isOccupied(int x, int y);
	void setPiece(int x, int y, char piece);
};

#endif
