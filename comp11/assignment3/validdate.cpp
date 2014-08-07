
//This command tells the compiler to
//include the library related to input/output

#include <iostream> //comments look like this too

//This is required to use cin cout without extra specification.
using namespace std;

const int Jan=1, Feb=2, Mar=3, Apr=4, May=5, Jun=6, Jul=7, Aug=8, Sep=9, Oct=10, Nov=11, Dec=12;

int getDay(int birthDate);
int getMonth(int birthDate);
bool isValidMonth(int potentialMonth);
int getYear(int birthDate);

int main()
{
    int userBDay;
    int userMonth;
    int userYear;
    int userDay;    
    
    cout << "Please enter in your birthday: ";
    
    cin >> userBDay;
    
    userDay = getDay(userBDay);

    userMonth = getMonth(userBDay);

    userYear = getYear(userBDay);

//Cascading conditional to seperate months by number of days and check that the month/day combination is valid
//Nested conditional to allow Feb 29 to be a valid date if userYear is a leap year
    if((userMonth==Jan)||(userMonth==Mar)||(userMonth==May)||(userMonth==Jul)||(userMonth==Aug)||(userMonth==Oct)||(userMonth==Dec))
    {
	if((userDay<=31)&&(userDay>=1))	
	    cout << "Y" << endl;
	else
	    cout << "N" << endl;
    }
    else if((userMonth==Apr)||(userMonth==Jun)||(userMonth==Sep)||(userMonth==Nov))
    {
	if((userDay<=30)&&(userDay>=1))
	    cout << "Y" << endl;
	else
	    cout << "N" << endl;
    }
    else if(userMonth==Feb)
    {
	if((userDay<=28)&&(userDay>=1))
	    cout << "Y" << endl;
	else if((userDay==29)&&(userYear%400==0))
	    cout << "Y" << endl;
	else if((userDay==29)&&(userYear%4==0)&&(userYear%100!=0))
	    cout << "Y" << endl;
	else 
	    cout << "N" << endl;
    }
    else
    {
	cout << "N" << endl;
    }
    
    return 0;  
}

int getDay(int birthDate)
{
    int day;
    day = (birthDate%100);
    return day;
}

int getMonth(int birthDate)
{
    int month;
    int year = getYear(birthDate);
    int yearShifted = year*10000;
    month = (birthDate - yearShifted)/100;
    return month;
}

int getYear(int birthDate)
{
    int year;
    year = birthDate/10000;
    return year;
}

bool isValidMonth(int potentialMonth)
{
    bool validity;
    validity=(potentialMonth>=1)&&(potentialMonth<=12);
    return validity;
}

