//
// sMain.cpp
// created by Aaron Tietz Jan 2011
//

#include <iostream>
#include "queue.h"
using namespace std;

const int ARRAY_SIZE = 10;

int main(){

  Queue one, two;
  string data[ARRAY_SIZE] = {"first", "second","third", "fourth", "fifth",
  	"sixth","seventh","eighth", "ninth", "tenth"};
  	
  // add strings to first queue
  for(int i = 0; i < ARRAY_SIZE; i++) {
    one.add(data[i]);
  }
  
  for(int i = 0; i < 3; i++) {
    cout << one.getFront() << endl;	// Should show first three times each on a 
                                        // line with a blank line at the end
  }
    
  // -- Remove and print everything from one
  while ( ! one.isEmpty()) {
    cout << one.remove() << endl;	// Should show first-tenth each on a 
    					// line with a blank line at the end
  }
    
  // -- Add all the values again
  for(int i = 0; i < ARRAY_SIZE; i++) {
      one.add(data[i]);
  }
 
/*   TEST FOR APPEND AND SPLIT FUNCTIONS.  ONLY REMOVE COMMENT WHEN 
     YOU GET TO THOSE FUNCTIONS */

  // -- Add all the string to two
  for(int i = 0; i < ARRAY_SIZE; i++) {
    two.add(data[i]);
  }
  
  // -- Split back half of one, append it to two
  /* Queue * one_backhalf = one.split();
   two.append(one_backhalf);

  // -- Remove and print everything from two
  while ( ! two.isEmpty()) {
    cout << two.remove() << endl;	// Should show sixth-tenth each on a 
    					// line with a blank line underneath
  }

  Queue test;
  test.add("Hello");
  test.add("World");
  two.append( &test);

  while ( ! test.isEmpty()) {
    cout << test.getFront() << endl;	// Should cout a blank line 
  }
  */
  return 0;
}
