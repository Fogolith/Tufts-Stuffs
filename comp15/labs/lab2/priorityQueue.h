// 
// priorityQueue.h
// Created by Aaron Tietz February 5, 2012
//

#ifndef AARON_PRIORITY_QUEUE_H
#define AARON_PRIORITY_QUEUE_H

#include "Node.h"
#include "WorkOrder.h"
#include <string>


class priorityQueue{
/*
		CLASS INVARIANTS: 
		1. front is either NULL or points to the Node with the highest priority level
*/
public:
  priorityQueue();
    // Postconditions: front is set to NULL
   
  void insertWithPriority(WorkOrder data);
    // Precondition: queue is empty or not empty
    // Postconditions: queue is not empty, Node has been inserted
    //	according to it's priority level
       
  WorkOrder removeHighestPriorityNode();
    // Precondition: queue is empty or not empty
    // Postconditions: if queue is empty, a WorkOrder object with name = "" and
    //  priorityLevel = 0.0 is returned, else a copy of the highest priority 
    //	Node's Order object
    
  bool isInQueue(std::string searchTerm) const;
    // Precondition: searchTerm is in queue or not 
    // Postcondition: returns true if term is in list, else false
    
  int remove(std::string searchTerm); 
    // Precondition: searchTerm is in queue or not 
    // Postcondition: any instances of searchTerm are deleted from the queue,
    //	returns number of Nodes removed
    
  bool isEmpty() const;
    // Precondition: queue is empty or not empty
    // Postcondition: returns true if queue is empty, else false
    
  ~priorityQueue();
    // Postcondition: Any Nodes in the queue are de-allocated
private:
  Node* front;
};

#endif
