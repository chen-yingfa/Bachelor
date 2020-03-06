#include <iostream>
#include <string.h>
#include "chessBoard.cpp"
#include "player.cpp"
using namespace std;

void mainMenu();
void gameInit();
void helpInit();

void playGame(ChessBoard chessBoard);
char colors[2] = {'X', 'O'};

int main() {
	mainMenu();
	
	return 0;
}

void mainMenu(){
	while (true){
		int com;
		cout << "1: play" << endl;
		cout << "2: help" << endl;
		cout << "3: exit" << endl;
		cin >> com;
		if (com == 1) gameInit();
		else if (com == 2) helpInit();
		else if (com == 3) return;
	}
}

void gameInit(){
	int m, n;
	cout << "Number of rows: ";
	cin >> m;
	cout << "Number of columns: ";
	cin >> n;
	ChessBoard chessBoard(m, n);
	playGame(chessBoard);
}

void helpInit(){
	cout << "------------------------" << endl;
	cout << "No help available yet." << endl;
	mainMenu();
}

void playGame(ChessBoard chessBoard){
	int turn = 0, com; //0 goes first (X)
	Player black(colors[0]);
	Player white(colors[1]);
	Player* curPlayer = &black;
	while (true){
		chessBoard.show();
		
		if (curPlayer == &black)
			cout << " -- Black's turn -- " << endl;
		else
			cout << " -- White's turn --" << endl;

		cout << "1: Places a piece" << endl;
		cout << "2: Exit to main menu" << endl;
		
		cin >> com;
		
		if (com == 1){
			int x, y;
			cout << "position <x> <y>: ";
			cin >> x >> y;
			if (chessBoard.isOccupied(x, y)){
				cout << "[!] A piece has already been placed there!" << endl;
				continue;
			}
			(*curPlayer).setChess(&chessBoard, x, y);
		} else if (com == 2) 
			break;
		else 
			continue;
		
		if (curPlayer == &black) {
			curPlayer = &white;
		} else {
			curPlayer = &black;
		}
	}
	
	mainMenu();
}

