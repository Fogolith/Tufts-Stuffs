//
// snow.cpp - a simulation snow falling at Halligan Hall
//
// note: this program has to be compiled with screendraw.cpp which has
//	 the functions that put characters on the screen at specific spots
//
#include  <iostream>
#include  "screendraw.h"
using namespace std;

// Define where on the screen the building and door are drawn.
// The coordinate system has (0,0) in upper left corner of screen.
// The coordinates are given as (row, col) (not (x,y) as in math).

const int BLDG_UPPER_LEFT_ROW = 6;
const int BLDG_UPPER_LEFT_COL = 9;
const int BLDG_WIDTH          = 27;
const int BLDG_HEIGHT         = 9;
const int DOOR_UPPER_LEFT_ROW = 10;
const int DOOR_UPPER_LEFT_COL = 36;
const int DOOR_WIDTH          = 2;
const int DOOR_HEIGHT         = 5;
const int GROUND              = 15;
const int GROUND_LEN          = 60;

// function declarations
void draw_student();
void draw_ground(int);
void draw_building();
void h_line(char, int, int, int);
void v_line(char, int, int, int);
void snow_storm(int);
void plow_snow();

int main()
{
	int	depth;

	cout << "How many feet of snow fall? ";
	cin  >> depth;
	
	clear_screen();

	draw_student();
	draw_ground(GROUND);
	draw_building();

	snow_storm(depth);
	plow_snow();
	
	place_cursor(17,0);
	return 0;
}
//
// draw_student (head_row, head_col)
//    purpose: draw a picture of a student with head at (row,col)
//
void draw_student()
{
	place_char('O', 11, 42);
	place_char('|', 12, 42);
	place_char('-', 12, 41);
	place_char('-', 12, 43);
	place_char('|', 13, 42);
	place_char('/', 14, 41);
	place_char('\\', 14, 43);
}
//
// draw_ground(row)
//    purpose: draw a row of '=' to look like the ground
//       idea: draw a whole bunch of '=' using place_char
//    problem: this is repetitive and boring
//
void draw_ground(int r)
{
    for(int i=0; i<GROUND_LEN; i++)
    {
	place_char('=', r,  i);
    }

}

// draw_building()
//   purpose: draw the building and its door
//   This needs to be changed to draw a solid building not just an outline
//
void draw_building()
{
	h_line('#', BLDG_UPPER_LEFT_ROW, BLDG_UPPER_LEFT_COL, BLDG_WIDTH);
	v_line('#', BLDG_UPPER_LEFT_ROW, BLDG_UPPER_LEFT_COL, BLDG_HEIGHT);
	v_line('#', BLDG_UPPER_LEFT_ROW, BLDG_UPPER_LEFT_COL+BLDG_WIDTH-1, 
					BLDG_HEIGHT);
	v_line('|', DOOR_UPPER_LEFT_ROW, DOOR_UPPER_LEFT_COL, DOOR_HEIGHT);
	v_line('|', DOOR_UPPER_LEFT_ROW, DOOR_UPPER_LEFT_COL+1, DOOR_HEIGHT);
}

//
// h_line(chr, start_row, start_col, len)
//   purpose: draw a horizontal line made of the char 'chr'
//            starting at (start_row, start_col) of length 'len'
//
void h_line(char c, int start_row, int start_col, int len)
{
    for(int i=0; i<len; i++)
    {
	place_char(c, start_row, start_col+i);
	    }
}

//
// v_line(chr, start_row, start_col, len)
//   purpose: draw a vertical line made of the char 'chr'
//            starting at (start_row, start_col) of length 'len'
//
void v_line(char c, int start_row, int start_col, int len)
{
    for(int i=0; i<len; i++)
    {
	place_char(c, start_row+i, start_col);
	    }
}

//
// snow_storm(depth)
//  simulate a snow storm by dropping one row of snow each second
//
void snow_storm(int depth)
{
	int	i;
	int 	row;

	row = GROUND-1;
	for(i=0; i<depth; i++)
	{
		h_line('*', row, 0, GROUND_LEN);
		row--;
		sleep(1);
	}
}

//
// plow_snow()
//  simulate snow plowing by driving a vertical line of '('s 
//  across the scene leaving blank spaces behind
//  You can leave a blank column by printing the ' ' space char
void plow_snow()
{
    int column=0
;
    for(int i=column; i<GROUND_LEN; i++)
    {

	v_line(' ', BLDG_UPPER_LEFT_ROW, column-1, GROUND-6);
	v_line('(', BLDG_UPPER_LEFT_ROW, column, GROUND-6);

    column++;

    usleep(60000);

    }
    
}
