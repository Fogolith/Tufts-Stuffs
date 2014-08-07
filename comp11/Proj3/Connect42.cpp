//Connect 4-2
//Jake Austin
//November __, 2011
//Program is a Connect 4 game that is played by 1 user and an AI

#include <iostream>
using namespace std;

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
string compName="computer";
space Board[7][7];
int spaceCount=42;	  //number of playable spaces on board

string getName1();
void initializeGame();
void printBoard();
int p1Turn(string name);

int horizontalCheck(int value);
int verticalCheck(int value);
int rDiagCheck(int value);
int lDiagCheck(int value);
int checkCanWin(int value);
int AITurn();
bool checkDraw();
bool checkWin(string name, int playerValue);
void gamePlay();
void playAgain();


int main()
{  
    
    gamePlay();
    return 0;
}


//FUNCTION DEFINITIONS

//gamePlay
//purpose    runs game (manages turn functions and checks for wins/draw) 
//           until players decide NOT to replay
//argument   strings for player names to be passed to other functions
//returns    -nothing-
// 
void gamePlay()
{
    string p1Name=getName1();   
    bool win=false;
    bool draw=false;
    initializeGame();
    printBoard();
    while(win==false)
    {
	spaceCount=p1Turn(p1Name);
	
	printBoard();
	win=checkWin(p1Name, p1win);
	if(win==true)
	{    
	    playAgain();
	    break;                    //'break' used to exit the gamePlay loop
                                      // if players select not to replay.
	}	                      //hasn't been taught but I found it
	spaceCount=AITurn();
       
	printBoard();     //was the easiest way to exit
	win=checkWin(compName, AIwin);    //the loop at the user's prompt
	if(win==true)
	{   
	    playAgain();
	    break;   
	}
	draw=checkDraw();
	if(draw==true)
	{
	    playAgain();
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
   cout << endl << endl << endl << endl;
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
					i=-1;
				}	
			}
		    	
	  	}
	}
    }	
	
    a=(a-1);    
    
    return a;				   //returns spaceCount-1
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
    for(int j=0; j<4; j++)      //checks for right-facing diagnals
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j+1].value)+(Board[i+2][j+2].value)+(Board[i+3][j+3].value))==playerValue)
	    {
		cout << "Congratulations " << name << '!' << endl;
		win=true;
	    }
	}
    }
    for(int j=6; j>2; j--)		//checks for left-facing diagnals
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j-1].value)+(Board[i+2][j-2].value)+(Board[i+3][j-3].value))==playerValue)
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
void playAgain()
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
	gamePlay();
    }
    else
    {
	cout << "Thank you for playing!" << endl;

    }
}


//AI functions to be used for Proj3
//
//
//checkBlock
//purpose     checks if player can win on next turn
//argument      ---
//returns     int - column for AI to play in
int checkCanWin(int value)
{
    int select=-1;
    
    
    select=horizontalCheck(value);
    if(select!=-1)
	return select;

    select=verticalCheck(value);
    if(select!=-1)
	return select;

    select=rDiagCheck(value);
    if(select!=-1)
	return select;

    select=lDiagCheck(value);
    if(select!=-1)
	return select;
    
    return select;
}

//AI move
//purpose   if not winning/blocking, chooses a space that does not create a user win on the following turn
//argument
//returns   int column to play in
void AImove()
{
    
    int select;
    int columnPlay[7];
    for(int i=0; i<7; i++)
	columnPlay[i]=0;

    for(int j=0; j<7; j++)
    {	
	for(int i=5; i>=0; i--)
	{
	    if(Board[i][j].value==0)
	    {
		Board[i][j].value=-1;
		select=checkCanWin(p1CanWin);
		if(select!=-1)
		{
		    columnPlay[j]=0;
		    Board[i][j].value=0;
		    i=-1;
		}
		else if(select==-1)
		{
		    Board[i][j].value=0;
		    columnPlay[j]=1;
		    i=-1;
		}
	       
	    }
	    
	}
    }
    int check=0;
    int total=0;
    int x=rand()%7;
    for(int i=0; i<7; i++)
    {
	total=(total+columnPlay[i]);
    }

    while(check==0)
    {
	if(total==0)
	{
 		for(int j=0; j<7; j++)
    		{
   			if(Board[0][j].value!=0) 
			{          
	    			columnPlay[j]=0;

			}
			else if(Board[0][j].value==0)
        		{
	   			 columnPlay[j]=1;
        		}
		}
		if(columnPlay[x-1]==1)
		{
			for(int i=5; i>=0; i--)
	    		{
				if(Board[i][x-1].value==0)
				{
	    				Board[i][x-1].value=AIvalue;
	    				Board[i][x-1].display=AIdisplay;
	    				check=1;
					break;
				}
	    		}				
		}
		else
		{
	    		x=rand()%7;
		}
	}

	if(columnPlay[x-1]==1)
	{
	    for(int i=5; i>=0; i--)
	    {
		if(Board[i][x-1].value==0)
		{
	    		Board[i][x-1].value=AIvalue;
	    		Board[i][x-1].display=AIdisplay;
	    		check=1;
			break;
		}
	    }
	}
	else
	{
	    x=rand()%7;
	}
    }
}


//AITurn
//purpose   manages computers turns
//argument
//returns   modified spaceCount
int AITurn()
{
    int a=spaceCount;
    int block=-1;
    int canWin=-1;
    block=checkCanWin(p1CanWin);
    canWin=checkCanWin(AICanWin);
    cout << compName << " is calculating..." << endl;
    sleep(1);
    if(canWin!=-1)
    {
	for(int i=6; i>=0; i--)
	{
	    if(Board[i][canWin].value==0)
	    {
		Board[i][canWin].value=AIvalue;
		Board[i][canWin].display=AIdisplay;
		i=-1;
	    }
	}
		
    }
    else if(block!=-1)
    {
	for(int i=6; i>=0; i--)
	{
	    if(Board[i][block].value==0)
	    {
		Board[i][block].value=AIvalue;
		Board[i][block].display=AIdisplay;
		i=-1;
	    }
	}
    }
    else
    {
	AImove();
    }
 a=(a-1);    
 
    return a;
}

int horizontalCheck(int value)
{   
 	int select=-1;
    	for(int i=0; i<6; i++)	 	 //loop that checks for sum value 3 in four consecutive horizontal spaces
    	{						 	
		for(int j=0; j<4; j++)
		{
	    		if(((Board[i][j].value)+(Board[i][j+1].value)+(Board[i][j+2].value)+(Board[i][j+3].value))==value)
	    		{
		
				if(i==5)                      //computer blocks it if found in bottom row
				{
		    			if(Board[i][j].value==0)
		    			{
						select=j;
			
		    			}
		    			else if(Board[i][j+1].value==0)
		    			{
						select=j+1;
		       
		    			}
		    			else if(Board[i][j+2].value==0)
		    			{
						select=j+2;
			
		    			}
		    			else if(Board[i][j+3].value==0)
		    			{
						select=j+3;
			
		    			}
				}
				else                       //computer checks that space BELOW winning space is occupied, otherwise does not play
				{
					if(Board[i][j].value==0)
					{
		    		
						if(Board[i+1][j].value!=0)
				    		select=j;
					}
					else if(Board[i][j+1].value==0)
					{
		    		
						if(Board[i+1][j+1].value!=0)
				    		select=j+1;
					}
					else if(Board[i][j+2].value==0)
					{
		    		
						if(Board[i+1][j+2].value!=0)
				    		select=j+2;
					}
					else if(Board[i][j+3].value==0)
					{
						if(Board[i+1][j+3].value!=0)
				    		select=j+3;
					}
	      			}
	   		}
		}
    	}
    
return select;
}

int verticalCheck(int value)
{
    int select=-1;
  for(int j=0; j<7; j++)	  //loop that checks board for sum value 3 in 4 consecutive vertical spaces
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j].value)+(Board[i+2][j].value)+(Board[i+3][j].value))==value)
	    {
		select=j;
	    }

	}
    }
  return select;
}

int rDiagCheck(int value)
{
    int select=-1;
 for(int j=0; j<4; j++)      //checks for sum value 3 in 4 consecutive spaces in a right-facing diagnal
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j+1].value)+(Board[i+2][j+2].value)+(Board[i+3][j+3].value))==value)
	    {
	      
	        if(Board[i][j].value==0)           //checks which space to block/ that space BELOW the block is occupied
		{
		    if(Board[i+1][j].value!=0)
		    select=j;
		}
		else if(Board[i+1][j+1].value==0)
		{
		    if(Board[i+2][j+1].value!=0)
		    select=j+1;
		}
		else if(Board[i+2][j+2].value==0)
		{
		    if(Board[i+3][j+2].value!=0)
		    select=j+2;
		}
		else if(Board[i+3][j+3].value==0)
		{
		    if(i==2)
		    {
			select=j+3;
		    }
		    else
		    {
		    	if(Board[i+4][j+3].value!=0)    
		    	select=j+3;
		    }
		} 
	    }
	}
    }
 return select;
}

int lDiagCheck(int value)
{
    int select=-1;
for(int j=6; j>2; j--)		//checks for sum value 3 in 4 consecutive spaces in a left-facing diagnal
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j-1].value)+(Board[i+2][j-2].value)+(Board[i+3][j-3].value))==value)
	    {
		if(Board[i][j].value==0)          //checks that space BELOW winning space is occupied
		{
		    if(Board[i+1][j].value!=0)
		    select=j;
		}
		else if(Board[i+1][j-1].value==0)
		{
		    if(Board[i+2][j-1].value!=0)
		    select=j-1;
		}
		else if(Board[i+2][j-2].value==0)
		{
		    if(Board[i+3][j-2].value!=0)
		    select=j-2;
		}
		else if(Board[i+3][j-3].value==0)
		{
		    if(i==2)
		    {
			select=j-3;	
		    }
		    else
		    {
			if(Board[i+4][j-3].value!=0)
		        select=j-3;
		    }
		}  	
	    }
	}
    }
return select;
}
