#include <vector>
#include "chessBoard.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H


class Player {
private:
	char name[20];
	char chessType;
public:
	Player(char color);
	bool setChess(ChessBoard *b, int x, int y);

};

#endif
