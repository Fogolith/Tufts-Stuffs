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
int getDate();
int fillBdayList(int bd[], int num);
void giveDates(int dates[], int start, int end, int num);

int main()
{
	int	bdays[LIST_SPACE];	// where data are stored
	int	pos;			// position variable
	int numItems;                   //number of datapoints
	int	firstDate, lastDate;	// define a range
	int	count ;			// used to count matching dates

	cout << "Enter first date in range:";
	firstDate=getDate();

	cout << "Enter last date in range:";
	lastDate=getDate();

	if ( lastDate < firstDate ){
		cout << "End cannot precede start" << endl;
		return 1;
	}

	cout << "How many birthdays will you enter? ";
	cin  >> numItems;
	cout << endl;
	if ( numItems > LIST_SPACE ){
		cout << "I only have space for " << LIST_SPACE << endl;
		return 1;
	}

	fillBdayList(bdays, numItems);

				// blank before output
	// search the list for matching records, count as we find them
	giveDates(bdays, numItems, firstDate, lastDate, numItems);


	return 0;
}

//Function Declarations

//function: getDate
//input:   -nothing-
//output    int
//
//purpose:  Get date and return it
int getDate()
{
    int date;
    cin >> date;
    return date;
}

//function: fillBdayList
//input:    int bd[], int num
//output:   void
//
//purpose:  fill an array with birthdays
int fillBdayList(int bd[], int num)
{
    int pos=0;
   
    	for( pos=0; pos<num; pos++ )	// read in data
	{
		cin >> bd[pos];		// store in array
	}
	return 0;
}

void giveDates(int dates[], int start, int end, int num)
{
    int pos=0;
    int count;
	for( count=0, pos=0; pos<num; pos++ )
	{
		if( (dates[pos] >= start) && (dates[pos] <= end) ){
			cout << pos << ". " << dates[pos] << endl;
			count++;
		}
	}
	cout << count << endl;
}
