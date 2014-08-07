// 
// queue.h
// Created by Aaron Tietz January 2012
//

#ifndef AARON_QUEUE_H
#define AARON_QUEUE_H

#include <iostream>
using namespace std;

struct Node{
  string value;
  Node* next;
};

class Queue{
public:
  Queue();
    // Postcondition: front, back are NULL
    
  void add(string newValue);
    // Postcondition: string is copied into a new Node that is added 
    //  to the end of the list 
    
  string remove();
    // Precondition: list is empty or not empty 
    // Postcondition: if list is not empty, value of string in the first 
    //  Node is returned and Node is deleted, else an empty string 
    //  is returned("").  
    
  string getFront() const;
    // Precondition: list is empty or not empty 
    // Postcondition: if list is not empty, value of string in the first 
    //  Node is returned, else an empty string is returned("").  List is
    //  unchanged.
    
  bool isEmpty() const;
    // Postcondition: returns true if list is empty, else false

  void print() const;
    // Postcondition: prints the strings in the queue in order from
    //   front to back
  
/*   TO UN-COMMENT AND WORK ON AFTER SUCCESSFULLY COMPLETING 
     AND TESTING THE ABOVE FUNCTIONS 
    
  void append(Queue * other);
    // Precondition: other points to another queue (or is NULL)
    // Postcondition: take all of the nodes from other and append them
    //   to the back of this queue.
    //   Two questions:
    //      (a) Can you do this in constant time?
    //      (b) What happens to the old list? Is it destroyed? Modified?
    
  Queue * split();
    // Precondition: list is empty or not empty 
    // Postcondition: return a new queue that holds the back half of
    //   the original list of items. This queue continues to hold the
    //   first half of the original list
    
*/
    
private:

  Node * front;
  Node * back;

};

#endif
