#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

/*

Definition of a connect4 Class
	A connect4 is a set of functions and constants
	necessary for a 1-player connect 4 game.
	
	There is a struct "space" with an int for playervalue
	and a char for the gameboard display, and constants for
	the player/AI space values, win values, and potential
	win values.

*/

struct space
{
    int value;
    char display;
};

const int p1value = 1;
const int AIvalue =-1;
const char p1display = 'R';
const char AIdisplay = 'Y';
const int p1CanWin=3;
const int AICanWin=-3;
const int p1win = 4;
const int AIwin =-4;
const string compName="computer";



class Connect4
{

public:

//Constructor that sets gameboard values/displays to 0/" ", sets bottom row
    Connect4();

//a function gamePlay that manages turns and checks for wins/draws
    void gamePlay();


private:

//int to keep track of how many playable spaces remain
    int spaceCount;

//array of arrays of struct space for the gameboard
    space Board[7][7];

//function to take in player name
    string getName1();

//functio to initialize gameboard values/displays, prints board first time
    void initializeGame();

//function to print the board to the screen, in a gameplay-grid
    void printBoard();

//function that checks board for potential horizontal wins 
//(4 spaces with value 3/-3)
    int horizontalCheck(int playerValue);

//function that checks board for potential vertical wins (4 spaces with 
//value 3/-3)
    int verticalCheck(int playerValue);

//function that checks board for potential right-diagonal wins (4 spaces 
//with value 3/-3)
    int rDiagCheck(int playerValue);

//function that checks board for potential left-diagonal wins (4 spaces 
//with value 3/-3)
    int lDiagCheck(int playerValue);

//function that checks for when all gameboard spaces are full
    bool checkDraw();

//function that checks if a player/AI has won
    bool checkWin(string name, int playerValue);


//AI function that checks if IT can win
    int checkCanWin(int value);

//function to manage player's turn, takes in name
    int p1Turn(string name);

//AI function that manages the AI's turn
    int AITurn();

//AI function that makes random move if not winning/blocking
    void AIMove();

//function that asks if another game is wanted/sets up new game
    void playAgain();

};
