/*
 *  main.cpp
 *  Konane
 *
 *  Created by ablumer on 12/26/13.
 *  Copyright 2013. All rights reserved.
 *
 *  The main program for playing a game of Konane
 *  The board can be any rectangular size up to MAX_ROWS x MAX_COLS
 *     (defined in Board.h)
 *  In verbose mode the board is printed after every move
 *  Current assumptions are:  One game with two players
 *     Either player can be controlled by a human or a computer
 *     The computer player can either play randomly or calculate
 *        a minimax optimal move at a specified search depth
 *     The first player can play 'x' or 'o'
 */
 
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "Board.h"
#include "Player.h"

int main (int argc, char * const argv[]) {
	char mode = 's';
	unsigned rows = 10;
	unsigned cols = 10;
	char playerType1 = 'r';
	char playerType2 = 'r';
	char playerPiece1 = 'x';
	char playerPiece2 = 'o';
	unsigned depth1 = 4;
	unsigned depth2 = 4;
	bool gameOver;
	
	if (argc == 1) {
		do {
			cout << "Verbose (v) or silent (s)? ";
			cin >> mode;
			if ( (mode != 'v') && (mode != 's') ) {
				cout << "Please enter v or s" << endl;
			}
		} while ( (mode != 'v') && (mode != 's') );
		do {
			cout << "How many rows? ";
			cin >> rows;
			if ( (rows < 1) || (rows > MAX_ROWS) ) {
				cout << "Must be between 1 and " << MAX_ROWS << endl;
			};
		} while ( (rows < 1) || (rows > MAX_ROWS) );
		do {
			cout << "How many columns? ";
			cin >> cols;
			if ( (cols < 1) || (cols > MAX_COLS) ) {
				cout << "Must be between 1 and " << MAX_COLS << endl;
			};
		} while ( (cols < 1) || (cols > MAX_COLS) );
		do {
			cout << "Is player 1 human (h), random (r), or minimax (m)? ";
			cin >> playerType1;
			if ( (playerType1 != 'h') && (playerType1 != 'r') && (playerType1 != 'm') ) {
				cout << "Please enter h, r, or m" << endl;
			}
		} while ( (playerType1 != 'h') && (playerType1 != 'r') && (playerType1 != 'm') );
		if (playerType1 == 'm') {
			cout << "What is the search depth for player 1? ";
			cin >> depth1;
		}
		do {
			cout << "Is player 1 playing x or o? ";
			cin >> playerPiece1;
			if ( (playerPiece1 != 'x') && (playerPiece1 != 'o') ) {
				cout << "Please enter x or o" << endl;
			}
		} while ( (playerPiece1 != 'x') && (playerPiece1 != 'o') );
		do {
			cout << "Is player 2 human (h), random (r), or minimax (m)? ";
			cin >> playerType2;
			if ( (playerType2 != 'h') && (playerType2 != 'r') && (playerType2 != 'm') ) {
				cout << "Please enter h, r, or m" << endl;
			}
		} while ( (playerType2 != 'h') && (playerType2 != 'r') && (playerType2 != 'm') );
		if (playerType2 == 'm') {
			cout << "What is the search depth for player 2? ";
			cin >> depth2;
		}
	}
	else {
		for (int i=1; i<argc; i++) {
			if (argv[i][0] != '-') {
				cout << "Invalid option: " << argv[i] << endl;
			}
			else if ((argv[i][1] == 'r') || (argv[i][1] == 'R')) {
				argv[i][0] = ' '; argv[i][1] = ' ';
				rows = atoi(argv[i]);
			}
			else if ((argv[i][1] == 'c') || (argv[i][1] == 'C')) {
				argv[i][0] = ' '; argv[i][1] = ' ';
				cols = atoi(argv[i]);
			}
			else if (argv[i][1] == '1') {
				if ((argv[i][2] == 'h') || (argv[i][2] == 'h')) {
					playerType1 = 'h';
				}
				else if ((argv[i][2] == 'r') || (argv[i][2] == 'R')) {
					playerType1 = 'r';
				}
				else if ((argv[i][2] == 'm') || (argv[i][2] == 'M')) {
					playerType1 = 'm';
					argv[i][0] = ' '; argv[i][1] = ' '; argv[i][2] = ' ';
					depth1 = atoi(argv[i]);
				}
				else {
					cout << "Unknown player type: " << argv[i][2] << endl;
				}
			}
			else if (argv[i][1] == '2') {
				if ((argv[i][2] == 'h') || (argv[i][2] == 'h')) {
					playerType2 = 'h';
				}
				else if ((argv[i][2] == 'r') || (argv[i][2] == 'R')) {
					playerType2 = 'r';
				}
				else if ((argv[i][2] == 'm') || (argv[i][2] == 'M')) {
					playerType2 = 'm';
					argv[i][0] = ' '; argv[i][1] = ' '; argv[i][2] = ' ';
					depth2 = atoi(argv[i]);
				}
				else {
					cout << "Unknown player type: " << argv[i][2] << endl;
				}
			}
			else if (argv[i][1] == 'h') {
				cout << "Usage: ./konane [-r <rows>] [-c <cols>] [-1 <p1type>] [-2 <p2type>]" << endl;
				cout << "   p1type and p2type can be human (h), random (r), or minimax (m)" << endl;
				cout << "   if player type is minimax, an optional integer gives the search depth" << endl;
				cout << "   For example: -2m3 specifies a maximum search depth of 3 for player 2" << endl;
				cout << "Defaults: -r10 -c10 -1r -2r" << endl;
				return 0;
			}
		}
	}
	Board myBoard( rows, cols );
	Player player1( playerType1, playerPiece1, depth1 );
	if (playerPiece1 == 'x') { playerPiece2 = 'o'; }
	else { playerPiece2 = 'x'; }
	Player player2( playerType2, playerPiece2, depth2 );
	player1.firstMove( myBoard );
	if (mode == 'v') { myBoard.printBoard( cout ); };
	gameOver = player2.secondMove( myBoard );
	if (mode == 'v') { myBoard.printBoard( cout ); };
	while (!gameOver) {
		gameOver = player1.nextMove( myBoard, mode );
		if (gameOver) {
			cout << "Player 2 wins." << endl;
			return 0;
		}
		if (mode == 'v') { myBoard.printBoard( cout ); };
		if (!gameOver) {
			gameOver = player2.nextMove( myBoard, mode );
			if (gameOver) {
				cout << "Player 1 wins." << endl;
				return 0;
			}
			if (mode == 'v') { myBoard.printBoard( cout ); };
		}
	}
    return 0;
}
