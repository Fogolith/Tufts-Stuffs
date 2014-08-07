//Jake Austin September 20, 2011
//This command tells the compiler to
//include the library related to input/output

#include <iostream> //comments look like this too

//This is required to use cin cout without extra specification.
using namespace std;

//function declarations
int getMonth(int birthDate);
int getYear(int birthDate);

int main()
{
    int userBDay;
    int userMonth;
    int userYear;
    
    //The following line sends output to the user. 
    //It defaults to the monitor. It is pronounced "see out". 
    //It is also called standard out.
    
    cout << "Please enter in your birthday: ";
    
 
    //The following line gets input from the user. 
    //The default is to get input from the keyboard.  
    //It is pronounced "see in" and is also called standard in
    
    cin >> userBDay;
    
    userMonth = getMonth(userBDay);
    userYear = getYear(userBDay);
  
    cout << userMonth << " " << userYear << endl;
    
    return 0;  
}

//Function Declarations Go Here

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

/* PS All of the comments in this 
   code are examples of bad comments
    in real life
*/
