#include <iostream>
using namespace std;
/*
 * mostpop.cpp
 *
 *   Analyze a set of lists of friends to find which person(s)
 *   is most popular.
 *
 *   Input: a list of ten people the count of their friends and the names of their friends
 *  Format: person-name0  count1  friend1 friend2 .... friend_count0
 *          person-name1  count2  friend1 friend2 .... friend_count1
 *          ...
 *          person-name9  count2  friend1 friend2 .... friend_count9
 *
 *  Output: Person with most friends: name count
 *          Most common friend: name count
 *
 *    Date: Put date here
 *      By: Your name here
 *
 */

const int	NUM_PEOPLE = 1;


struct Person {
	string	name;
	int	numFriends;
	string*	friends;		// What is the type?
};

struct isFriend
{
    int count;
    string name;
};

void	readInData(Person[], int);
void	whoHasMostFriends(Person[], int);
void	whoIsMostFriended(Person[], int);

int main()
{
	
	Person	People[NUM_PEOPLE];	// the main array

	readInData(People, NUM_PEOPLE);		// get data
	whoHasMostFriends(People, NUM_PEOPLE);	// answer question one
	whoIsMostFriended(People, NUM_PEOPLE);	// answer question two
	return 0;
}

// readInData(Person[], int num)
//   purpose: read data from cin, populate array
//      args: array to fill, number to expect
//   
void readInData(Person List[], int num)
{

    for(int i=0; i<num; i++)
    {
	cin >> List[i].name;
	cin >> List[i].numFriends;
	List[i].friends=new string[List[i].numFriends];
	for(int j=0; j<List[i].numFriends; j++)
	{
	    cin >> List[i].friends[j];
	}
    }
}

// whoHasMostFriends(Person[], int num)
//   purpose: find who in the list has the most friends
//      args: array to search, number of items
//    output: name and count for person with most
//      note: what if there is a tie?
//
void whoHasMostFriends(Person List[], int num)
{
    string winner;
    int mostFriends=0;
    for(int i=0; i<num; i++)
    {
	if(List[i].numFriends>mostFriends)
	{
	    mostFriends=List[i].numFriends;
	    winner=List[i].name;
	}
    }
 
}

// whoIsMostFriended(Person List[], int num)
//   purpose: find who in the friends lists is most common
//      args: array to search, number of items
//    output: name and count for person most often found
//      note: can there be a tie?
//
void whoIsMostFriended(Person List[], int num)
{
    isFriend popular[10000];
    int count=0;
    string winner="loser";
    int winCount=0;
    for(int a=0; a<1000; a++)
	popular[a].count=0;

    for(int i=0; i<num; i++)
    {
	for(int j=0; j<List[i].numFriends; j++)
	{
	    for(int a=0; a<count; a++)
	    {
		if(List[i].friends[j]==popular[a].name)
		{
		    a=count;
		    popular[a].count=(popular[a].count+1);
		}
		else
		{
		    popular[count].name=List[i].friends[j];
		    popular[count].count=(popular[count].count+1);
		}
	    }
	    count=(count+1);
	}
    }
    for(int i=0; i<10; i++)
    {
	if(popular[i].count>winCount)
	{
	    winner=popular[i].name;
	    winCount=popular[i].count;
	}
	cout << popular[i].name << endl;
    }
    cout << endl << winner;
}
