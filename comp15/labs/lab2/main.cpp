// 
// main.cpp
// Created by Aaron Tietz February 5, 2012
//

#include <iostream>
#include "priorityQueue.h"
#include "Node.h"
#include "WorkOrder.h"
using namespace std;

void priorityQueueTest();


int main(){
  priorityQueueTest();
  return 0; 
}


void priorityQueueTest(){
  priorityQueue pqOne;
  WorkOrder a("Halligan roof patch", 12.3), b("Ballou air conditioner maintenance", 11.2),
  	c("Eliot Pearson window replacement", 15.4), d("Mayer first floor paint", 7.2);
  	
  pqOne.insertWithPriority(a);
  pqOne.insertWithPriority(b);
  pqOne.insertWithPriority(c);
  pqOne.insertWithPriority(d);
   
  cout << "Should be 1: " << pqOne.isInQueue("Halligan roof patch") << endl;
  cout << "Should be 1: " << pqOne.isInQueue("Mayer first floor paint") << endl;
  cout << "Should be 0: " << pqOne.isInQueue("Tisch outer wash") << endl << endl;
  
  WorkOrder temp = pqOne.removeHighestPriorityNode();
  cout << "Should be 'Eliot Pearson window replacement': " << temp.Name() << endl;
  temp = pqOne.removeHighestPriorityNode();
  cout << "Should be 'Halligan roof patch': " << temp.Name() << endl;
  
  temp = pqOne.removeHighestPriorityNode();
  temp = pqOne.removeHighestPriorityNode();
  temp = pqOne.removeHighestPriorityNode();  
  
  cout << "Should be 1: " << pqOne.isEmpty() << endl;
  cout << "Should be blank: " << temp.Name() << endl << endl;
  
  pqOne.insertWithPriority(c);
  pqOne.insertWithPriority(d);
  pqOne.insertWithPriority(a);
  pqOne.insertWithPriority(b);
  
  pqOne.remove("Eliot Pearson window replacement");
  cout << "Should be 0: " << pqOne.isInQueue("Eliot Pearson window replacement") << endl;
  pqOne.remove("Halligan roof patch");
  cout << "Should be 0: " << pqOne.isInQueue("Halligan roof patch")
    << endl << endl;
  temp = pqOne.removeHighestPriorityNode();
  cout << "Should be 'Ballou air conditioner maintenance': " << temp.Name() 
   << endl << endl;
  cout << "Test program has fully executed.\n\n";
}
