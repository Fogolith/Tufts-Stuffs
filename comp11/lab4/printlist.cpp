#include <iostream>
/*
 * printlist.cpp  -- shows how to read a list of numbers into an array
 *
 *	1. First asks for the number of items in the list
 *	2. then uses a loop to read in that many values
 *	3. then prints out the list with line numbers using another loop
 */

using namespace std;

const int LIST_SPACE = 2000;		// size of array

int main()
{
	int	bdays[LIST_SPACE];	// where data are stored
	int	numItems;		// number of spaces used
	int	pos;			// position variable
	int rangeStart;
	int rangeEnd;
	int count=0;

	cout << "What is the starting date? ";
	cin >> rangeStart;
	    cout << "what is the end date ";
	cin >> rangeEnd;
	cout << "How many birthdays will you enter? ";
	cin  >> numItems;

	if ( numItems > LIST_SPACE ){
		cout << "I only have space for " << LIST_SPACE << endl;
		return 1;
	}

	// this loop is much shorter than
	//   cin >> bdays[0]
	//   cin >> bdays[1]
	//   cin >> bdays[2]
	//   ...
	//ask user for each bday they are entering, store in bdays array
	for( pos=0; pos<numItems; pos = pos+1)
	{
		cin >> bdays[pos];
	}

	// now we can print out the list with numbers
	for( pos=numItems-1; pos>=0; pos = pos-1)
	{
	    if((bdays[pos]>=rangeStart)&&(bdays[pos]<=rangeEnd))
	    {	cout << pos << ". " << bdays[pos] << endl;
		count++;
            }
	}
        cout << "There are " << count << endl;
	return 0;
}
