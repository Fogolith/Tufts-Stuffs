#include "ConnectFour.h"

//Constructor, initializes gameBoard
Connect4::Connect4()
{
    initializeGame();
    srand((unsigned)time(NULL));
}

//A function that manages gameplay/turns until players decide NOT to play
void Connect4::gamePlay()
{
    string p1Name=getName1();
    bool win=false;
    bool draw=false;
    while(win==false)
    {
	spaceCount=p1Turn(p1Name);	
	printBoard();
	win=checkWin(p1Name, p1win);
	if(win==true)
	{    
	    playAgain();
	    break;                 
                                    
	}	                      
	spaceCount=AITurn();      
	printBoard();     
	win=checkWin(compName, AIwin);    
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

//A function to take in player name
string Connect4::getName1()
{
    string Name;
    cout << "Player 1, please enter your name: ";
    cin >> Name;
    return Name;
    cout << endl;
}

//A function to initialize the board and set up a new game
void Connect4::initializeGame()
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
spaceCount=42;
}

//A function to print the gameboard to the screen in a frame
void Connect4::printBoard()
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

//A function that checks the board for potential horizontal wins
//ARGUMENT:  p1/AI value (3/-3)
//RETURNS:   column value for space that would win/block if necessary
int Connect4::horizontalCheck(int playerValue)
{   
    int select=-1;
    for(int i=0; i<6; i++)
    {						 	
    	for(int j=0; j<4; j++)
	{
            if(((Board[i][j].value)+(Board[i][j+1].value)+(Board[i][j+2].value)+(Board[i][j+3].value))==playerValue)
	    {
		
	        if(i==5) //if bottom row, find empty space and returns  
		{
		    if(Board[i][j].value==0)
		    select=j;
			
		    else if(Board[i][j+1].value==0)
	            select=j+1;
		       
		    else if(Board[i][j+2].value==0)
                    select=j+2;
		     
		    else if(Board[i][j+3].value==0)
		    select=j+3;
		       
		}
	        else    //all other rows check that space under is occupied
			//finds empty space and returns
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

//A function that checks the board for potential vertical wins
//ARGUMENT:    p1/AI value (3/-3)
//RETURNS:     column value for space that would win/block if necessary
int Connect4::verticalCheck(int playerValue)
{
    int select=-1;
    for(int j=0; j<7; j++)  
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j].value)+(Board[i+2][j].value)+(Board[i+3][j].value))==playerValue)
	    {
		select=j;
	    }

	}
    }
  return select;
}

//A function that checks the board for potential right diagonal wins
//ARGUMENT:   p1/AI value (3/-3)
//RETURNS:    column value for space that would win/block if necessary
int Connect4::rDiagCheck(int playerValue)
{
    int select=-1;
    for(int j=0; j<4; j++)   
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j+1].value)+(Board[i+2][j+2].value)+(Board[i+3][j+3].value))==playerValue)
	    { 
		                            //finds empty space, checks that
		                            //space under is occupied, returns
	        if(Board[i][j].value==0)         
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

//A function that checks the board for potential left diagonal wins
//ARGUMENT:   p1/AI value (3/-3)
//RETURNS:    column value for space that would win/block if necessary
int Connect4::lDiagCheck(int playerValue)
{
    int select=-1;
    for(int j=6; j>2; j--)	     
    {
	for(int i=0; i<3; i++)
	{
	    if(((Board[i][j].value)+(Board[i+1][j-1].value)+(Board[i+2][j-2].value)+(Board[i+3][j-3].value))==playerValue)
	    {
                                            //finds empty space, checks that
					    //space under is occupied, returns
		if(Board[i][j].value==0)      
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

//A function that checks if the board is full, hence a draw
bool Connect4::checkDraw()
{
    bool draw=false;
    if(spaceCount==0)
    {
	cout << "Draw!" << endl;             
	draw=true;
    }
    return draw;
}

//A function that checks for a player win
//ARGUMENT:    p1/AI win value (4/-4), string for name
//RETURNS:     bool
bool Connect4::checkWin(string name, int playerValue)
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

//An AI function that checks if the user/AI can win, blocks/wins if possible
//ARGUMENT:    player potential win value (3/-3)
//RETURNS:     int for column to play in to win/block
int Connect4::checkCanWin(int value)
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

//A funtion to take in a move from the user, bounds-checks and makes play
//ARGUMENT:    string for player name
//RETURNS:     modified count of spaces left on board
int Connect4::p1Turn(string name)
{
    int a=spaceCount;		          //takes current spaceCount
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

//An AI function to manage the computers turn
//ARGUMENT:    -none-
//RETURNS:     modified count of spaces left on board
int Connect4::AITurn()
{
    int a=spaceCount;
    int block=-1;
    int canWin=-1;

    cout << compName << " is calculating..." << endl;

    block=checkCanWin(p1CanWin);
    canWin=checkCanWin(AICanWin);

    if(canWin!=-1)                      //wins if it can
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
    else if(block!=-1)                  //blocks if it can't win, has to
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
    else			       //moves if it's not blocking/winning
    {
	AIMove();
    }
    a=(a-1);    
 
    return a;
}

//An AI function to move if not winning/blocking
//ARGUMENT:    -none-
//RETURNS:     -nothing-
void Connect4::AIMove() 
{
    
    int select;
    int columnPlay[7];			//array for column availability
    for(int i=0; i<7; i++)		//initialized as NOT playable
	columnPlay[i]=1;

    for(int j=0; j<7; j++)              //checks if column is full
    {
        if(Board[0][j].value!=0) 
	columnPlay[j]=0;
    }
    for(int j=0; j<7; j++)              //loop goes column by column
    {	
	for(int i=5; i>=0; i--)         //finds first playable space
	{
	    if(Board[i][j].value==0)    //simulates turn in free space
	    {
		Board[i][j].value=-1;
		select=checkCanWin(p1CanWin);//checks if move creates user win
		if(select!=-1)          //if a block is returned
		{
		    columnPlay[j]=0;    //marks column as not playable
		    Board[i][j].value=0;
		    i=-1;		//doesn't check spaces above first
		}   
		                    //playable space in column
		else                    //if NO block is returned
		{
		    Board[i][j].value=0;
		      
		    i=-1;		//doesn't check spaces above first
		}
	       
	    }
	    
	}
    }

    int check=0;
    int total=0;
    int x=rand()%7;

    for(int i=0; i<7; i++)		//calculates # total playable columns
    {
	total=(total+columnPlay[i]);
    }

    while(check==0)
    {
	if(total==0)		     //makes move if all moves create user win
	{
	    for(int j=0; j<7; j++) //resets array on ONLY availability
    	    {
   	        if(Board[0][j].value!=0) 
		columnPlay[j]=0;

	        else if(Board[0][j].value==0)
        	columnPlay[j]=1;
        		
	    }
	    if(columnPlay[x]==1)   //checks if rand# is playable column, plays
	    {
	        for(int i=5; i>=0; i--)
	        {
	            if(Board[i][x].value==0)
		    {
	    	        Board[i][x].value=AIvalue;
	    	        Board[i][x].display=AIdisplay;
	    	        check=1;
		        break;
		    }
	        } 				
	    }
	    else		   //otherwise, generate new rand# and restarts
	     x=rand()%7;
        }

	                           //if not all moves create user-win
        if(columnPlay[x]==1)//checks if rand# is playable column, plays
	{
	     for(int i=5; i>=0; i--)
	     {
		 if(Board[i][x].value==0)
		 {
		     Board[i][x].value=AIvalue;
		     Board[i][x].display=AIdisplay;
		     check=1;
		    
		     break;
		 }
	       	      
		   
	     }
	}
	else
	    x=rand()%7;
	
    }
}

//A function that asks the user if they want to play another game,
//can start a new game if user chooses to
//ARGUMENT:    -none-
//RETURNS:     -none-
void Connect4::playAgain()
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
	initializeGame();
	gamePlay();
    }
    else
    {
	cout << "Thank you for playing!" << endl;

    }
}
