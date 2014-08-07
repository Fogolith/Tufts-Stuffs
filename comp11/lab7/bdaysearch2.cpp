#include <iostream>
/*
 * bdaysearch2.cpp  -- search a list of birthdays for those in a range
 * TODO: write getNumber and use it in three places
 */

using namespace std;

const int LIST_SPACE = 2000;		// size of array

int getNumber(string ask, int min, int max);
void readData(int list[]);
void searchNCount(int list[], int first, int last);

int main()
{
	int	bdays[LIST_SPACE];	// where data are stored
	int	firstDate, lastDate;	// define a range
	
	firstDate = getNumber("Enter Start Date: ", 10101, 99991231);
	lastDate  = getNumber("Enter End Date: ", firstDate, 99991231);
		// read in range
	readData(bdays);
	searchNCount(bdays, firstDate, lastDate);
	return 0;
}


// purp: reads in the list
// rets: nothing
// args: the list to fill
// note: adds a -1 sentinel to end of list
void readData(int list[])
{
	
	int	numItems=getNumber("How Many Birthdays will you enter: ", 1, LIST_SPACE);     // number of spaces used


	int	pos;			// position variable
	for( pos=0; pos<numItems; pos++ )	// read in data
	{
		cin >> list[pos];		// store in array
	}
	list[pos] = -1;
}

//
// search the list, print out matchihng entries
// keep and report ac ount
//
void searchNCount(int list[], int first, int last)
{
	int	count ;			// used to count matching dates
	cout << endl;				// blank before output
					// search the list for matching records, count as we find them
	int	pos;			// position variable
	for( count=0, pos=0; list[pos] != -1 ; pos++ )
	{
		if( (list[pos] >= first) && (list[pos] <= last) ){
			cout << pos << ". " << list[pos] << endl;
			count++;
		}
	}
	cout << count << endl;
}

int getNumber(string ask, int min, int max)
{
    int input;
    cout << ask;
    cin >> input;
    if((input>=min)&&(input<=max))
    {
    return input;
    }
    else
	cout << "Invalid Entry" << endl;
    return 0;
}
