#include <iostream>
/*
 * bdaysearch.cpp  -- search a list of birthdays for those in a range
 *
 * action:
 *   1. asks user for a range of dates
 *   2. reads in a list of birthdays
 *   3. prints out and counts those items within the requested range
 *   4. returns: 1 if data problem, 0 if success
 *
 * shows:
 *   1. How to read in a list and store it in an array
 *   2. How to traverse an array searching for items that fit some condition
 *   3. How to use a counter
 */

using namespace std;

const int LIST_SPACE = 2000;		// size of array

int getDate();
void readData(int list[]);
void searchNCount(int list[], int first, int last);

int main()
{
	int	bdays[LIST_SPACE];	// where data are stored
	int	firstDate, lastDate;	// define a range

	firstDate = getDate();
	lastDate  = getDate();		// read in range
	readData(bdays);
	searchNCount(bdays, firstDate, lastDate);
	return 0;
}

//
// getDate
//   purp: read in a date from the user
//   arguments: none
//   returns: a date
//
int getDate()
{
	int	date;

	cout << "Enter a date: ";
	cin  >> date;
	return date;
}
// purp: reads in the list
// rets: nothing
// args: the list to fill
// note: adds a -1 sentinel to end of list
void readData(int list[])
{
	int	numItems;		// number of spaces used
	cout << "How many birthdays will you enter? ";
	cin  >> numItems;

	if ( numItems > LIST_SPACE ){
		cout << "I only have space for " << LIST_SPACE << endl;
		exit(1);
	}

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
