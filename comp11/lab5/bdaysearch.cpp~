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
 *
 * TODO: modularize using functions so main() becomes *really* short
 */

using namespace std;

const int LIST_SPACE = 2000;		// size of array

int main()
{
	int	bdays[LIST_SPACE];	// where data are stored
	int	numItems;		// number of spaces used
	int	pos;			// position variable
	int	firstDate, lastDate;	// define a range
	int	count ;			// used to count matching dates

	cout << "Start of range? ";
	cin  >> firstDate;
        cout << "End of range? ";
	cin  >> lastDate;
	if ( lastDate < firstDate ){
		cout << "End cannot precede start" << endl;
		return 1;
	}
	cout << "How many birthdays will you enter? ";
	cin  >> numItems;

	if ( numItems > LIST_SPACE ){
		cout << "I only have space for " << LIST_SPACE << endl;
		return 1;
	}

	for( pos=0; pos<numItems; pos++ )	// read in data
	{
		cin >> bdays[pos];		// store in array
	}

	cout << endl;				// blank before output
	// search the list for matching records, count as we find them
	for( count=0, pos=0; pos<numItems; pos++ )
	{
		if( (bdays[pos] >= firstDate) && (bdays[pos] <= lastDate) ){
			cout << pos << ". " << bdays[pos] << endl;
			count++;
		}
	}
	cout << count << endl;

	return 0;
}
