//
// golf.cpp
//	version: 2011-06-06 14:42
//	purpose: practice in writing user-defined functions
//	author:
//
#include <iostream>
#include <iomanip>
using namespace std;

// days of the week
const int SUN = 0, MON = 1, TUE = 2, WED = 3, THR = 4, FRI = 5, SAT = 6;

// constants for rules
const double	BASE_PRICE = 9.0;
const int	HIGH_TEMP_CUTOFF = 80;
const int	LOW_TEMP_CUTOFF = 65;
const double	PER_DEGREE_PENALTY = 0.10;
const int	EVENING_START = 17;
const double	WEEKDAY_DAY_PENALTY = 1.00;
const double	RAIN_PENALTY = 2.00;
const int	WIND_GRANULARITY = 15;
const double	WIND_PENALTY = 1.50;

// function declaration
double price(int tempF, int day, int hour, bool is_raining, int wind_mph) ;

// main function here
int main() 
{
	// define vars for input and a value used in the tests below
	int	tempF, dayOweek, hour, rainP, windMPH;
	double	value;

	// set the precision 
	cout << setiosflags(ios::fixed) << setprecision(2);
	
	// Get data from user
	cout << "Temperature (fahrenheit)? ";
	cin  >> tempF;

	cout << "Day of week (0=Sun, 1=Mon, ..., 6=Sat)? " ;
	cin  >> dayOweek;
	
	cout << "Hour of day (0..23)? ";
	cin  >> hour;

	cout << "Is it raining (0=no, 1=yes)? ";
	cin  >> rainP;

	cout << "Wind speed (MPH)? ";
	cin  >> windMPH;

	// compute the price based on these values
	value = price(tempF, dayOweek, hour, rainP, windMPH);

	cout << "Price: " << value << endl;
	return 0;
}
//
// function to compute the price based on various factors
//
double price(int temp_F, int day_of_week, int hour_of_day, 
			 bool is_raining, int wind_mph) 
{


	double currentPrice = BASE_PRICE;
	if(temp_F>HIGH_TEMP_CUTOFF)
{
		currentPrice = currentPrice - (temp_F - HIGH_TEMP_CUTOFF)*PER_DEGREE_PENALTY;
} 
	if(temp_F<LOW_TEMP_CUTOFF)
{
		currentPrice = currentPrice - (LOW_TEMP_CUTOFF - temp_F)*PER_DEGREE_PENALTY;
}
	if(day_of_week!=SAT)
{	
		if(day_of_week!=SUN)
		{
			if(hour_of_day<EVENING_START)
			{
				currentPrice = currentPrice - WEEKDAY_DAY_PENALTY;
}
}
}	
	if(is_raining==true)
{
		currentPrice = currentPrice - RAIN_PENALTY;
}
	currentPrice = currentPrice - (wind_mph/WIND_GRANULARITY)*WIND_PENALTY;
  return currentPrice;
}
