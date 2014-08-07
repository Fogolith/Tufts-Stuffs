//Connect 4
//Jake Austin
//November 7, 2011
//Program is a simplified Connect 4 game that does not check diagonal wins
//and is used by 2 human players
#include <iostream>
using namespace std;

struct space
{
    int value;
    char display;
};

const int p1value = 1;
const int p2value =-1;
const char p1display = 'R';
const char p2display = 'Y';
const int p1win = 4;
const int p2win =-4;
space Board[7][7];
int spaceCount=42;	  //number of playable spaces on board

string getName1();
string getName2();
void initializeGame();
void printBoard();
int p1Turn(string name);
int p2Turn(string name);
bool checkDraw();
bool checkWin(string name, int playerValue);
void gamePlay(string name1, string name2);
void playAgain(string name1, string name2);

int main()
{  
    string p1Name=getName1();
    string p2Name=getName2();
    gamePlay(p1Name, p2Name);
    return 0;
}


//FUNCTION DEFINITIONS

//gamePlay
//purpose    runs game (manages turn functions and checks for wins/draw) 
//           until players decide NOT to replay
//argument   strings for player names to be passed to other functions
//returns    -nothing-
// 
void gamePlay(string name1, string name2)
{
   
    bool win=false;
    bool draw=false;
    initializeGame();

    while(win==false)
    {
	spaceCount=p1Turn(name1);
	win=checkWin(name1, p1win);
	if(win==true)
	{    
	    playAgain(name1, name2);
	    break;                    //'break' used to exit the gamePlay loop
                                      // if players select not to replay.
	}	                      //hasn't been taught but I found it
	spaceCount=p2Turn(name2);     //was the easiest way to exit
	win=checkWin(name2, p2win);   //the loop at the user's prompt
	if(win==true)
	{   
	    playAgain(name1, name2);
	    break;   
	}
	draw=checkDraw();
	if(draw==true)
	{
	    playAgain(name1, name2);
	    break;
	}
	
    }
}

//getName   (made 2 functions to simplify before project 3)
//purpose   gets user input for player names
//argument  -none-
//returns   string
//
string getName1()
{
    string Name;
    cout << "Player 1, please enter your name: ";
    cin >> Name;
    return Name;
    cout << endl;
}
string getName2()
{
    string Name;
    cout << "Player 2, please enter your name: ";
    cin >> Name;
    return Name;
    cout << endl;
}

//initializeGame
//purpose     initializes values of board's indecies
//argument    -none-
//returns     -nothing-
//
void initializeGame()
{
    for(int i=0; i<7; i++)
    {
	if(i==6)	  //initializes bottom row to value/display 1-7
	{
	  
		Board[i][0].value=1;
		Board[i][0].display='1';
		Board[i][1].value=2;
		Board[i][1].display='2';  
		Board[i][2].value=3;
		Board[i][2].display='3';
		Board[i][3].value=4;
		Board[i][3].display='4';
		Board[i][4].value=5;
		Board[i][4].display='5';
		Board[i][5].value=6;
		Board[i][5].display='6';
		Board[i][6].value=7;
		Board[i][6].display='7';
	}
	else		   //initializes rest of board to value 0, display " "
	{
	    for(int j=0; j<7; j++)
	    {	
	    	Board[i][j].value=0;
	    	Board[i][j].display=' ';
	    }
	}
    }
printBoard();
}

//printBoard
//purpose    prints the gameBoard array in a printed grid
//argument   -none- 
//returns    -nothing-
//
void printBoard()
{
   string hLine="+---+---+---+---+---+---+---+";

   cout << hLine << endl;

   for(int i=0; i<7; i++)
   {
	for(int j=0; j<7; j++)
	{
	    cout << "| " << Board[i][j].display << ' ';
	}
	cout << '|' << endl << hLine << endl;
   }
}

//p1Turn
//purpose   takes in p1 move, checks bounds and claims space in array
//argument  string for p1 name
//returns   int reflecting the number of remaining playable spaces
//
int p1Turn(string name)
{
    int a=spaceCount;		          //takes current spaceCount (global)
    int input;
    cout << name << " Please select column (1-7) to play in" << endl;
    cin >> input;

    if((input>7)||(input<1))	          //checks that input is valid (1-7)  
    {
    	cout << "Invalid input" << endl;				
	p1Turn(name);
    }
    else if(Board[0][(input-1)].value!=0) //check that selected column is 
	                                  //available, if not restarts turn
    {
	cout << "column full" << endl;
	p1Turn(name);
    }
    else if((input<=7)&&(input>=1))	  //if valid, checks input column    
    {					  //for next available space 
	                                  //stores p1 value/display
    	for(int j=0; j<7; j++)
    	{
		if(Board[6][j].value==input)
		{ 
			for(int i=5; i>=0; i--)		
	    		{
				if(Board[i][(input-1)].value==0)
				{
					Board[i][(input-1)].value=p1value;
					Board[i][(input-1)].display=p1display;
					i=0;
				}	
			}
		    	
	  	}
	}
    }	
	
    a=(a-1);    
    printBoard();
    return a;				   //returns spaceCount-1
} 

//p2Turn
//
//same function as p1Turn, only stores -1&Y instead of 1&R
//
//
int p2Turn(string name)
{
    int a=spaceCount;				   
    int input;
    cout << name << " Please select column (1-7) to play in" << endl;
    cin >> input;

    if((input>7)||(input<1))		      	    
    {
    	cout << "Invalid input" << endl;				
	p2Turn(name);
    }
    else if(Board[0][(input-1)].value!=0)	     
    {
	cout << "column full" << endl;
	p2Turn(name);
    }
    else if((input<=7)&&(input>=1))		           
    {						     
    	for(int j=0; j<7; j++)
    	{
		if(Board[6][j].value==input)
		{ 
			for(int i=5; i>=0; i--)		
	    		{
				if(Board[i][(input-1)].value==0)
				{
					Board[i][(input-1)].value=-p2value;
					Board[i][(input-1)].display=p2display;
					i=0;
				}	
			}
		    	
	  	}
	}
    }	
	
    a=(a-1);    
    printBoard();
    return a;					       
} 

// checkDraw
//purpose   check if there are any playable spaces left
//argument  -none-
//returns   bool
//
bool checkDraw()
{
    bool draw=false;
    if(spaceCount==0)
    {
	cout << "Draw!" << endl;             
	draw=true;
    }
    return draw;
}

//checkWin
//purpose   check if a player has won the game
//argument  2 strings for player names
//returns   bool
//
bool checkWin(string name, int playerValue)
{
    bool win=false;
    for(int i=0; i<6; i++)	  //loop that checks board for horizontal wins
    {						 	
	for(int j=0; j<4; j++)
	{
	    if(((Board[i][j].value)+(Board[i][j+1].value)+(Board[i][j+2].value)+(Board[i][j+3].value))==playerValue)
	    {
		cout << "Congratulations " << name << '!' << endl;
		win=true;
	    }

	}
    }
    for(int j=0; j<7; j++)	  //loop that checks board for vertical wins
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j].value)+(Board[i+2][j].value)+(Board[i+3][j].value))==playerValue)
	    {
		cout << "Congratulations " << name << '!' << endl;
		win=true;
	    }

	}
    }
    return win;
}

//playAgain
//purpose    asks player(s) if they want to play another game, 
//           can start a new game
//argument   2 strings for player names
//returns    -nothing-
//
void playAgain(string name1, string name2)
{
    char answer;
    cout << "Would you like to play again? y/n" << endl;
    cin >> answer;

    while((answer!='y')&&(answer!='n'))
    {
	cout << "Please enter y or n" << endl;
	cin >> answer;
    }
    if(answer=='y')		   //resets Board and starts gamePlay over
    {
	spaceCount=42;
	gamePlay(name1, name2);
    }
    else
    {
	cout << "Thank you for playing!" << endl;

    }
}
