#include "player.h"
//#include "position.h"
#include "chessBoard.h"

using namespace std;

bool Player::setChess(ChessBoard* b, int x, int y){
	//returns false if piece can't be placed
	if (b->isOccupied(x, y)) return false;
	b->setPiece(x, y, chessType);
	return true;
}

Player::Player(char color) {
	chessType = color;
}
