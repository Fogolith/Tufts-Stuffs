#include <iostream>

using namespace std;
//
// functions to draw on terminal screen
// 
// coordinate system has (0,0) at upper left corner
// first coordinate is row second is col
//

void clear_screen()
{
	cout << "\033[2J";
	flush(cout);
}

void place_cursor(int row, int col)
{
	cout << "\033[" << (row+1) << ";" << (col+1) << "H";
	flush(cout);
}
void place_char(char c, int row, int col)
{
	place_cursor(row, col);
	cout << c;
	flush(cout);
}
