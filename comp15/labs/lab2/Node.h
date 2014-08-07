// 
// Node.h
// Created by Aaron Tietz February 5, 2012
//


#ifndef AARON_NODE_H
#define AARON_NODE_H

#include "WorkOrder.h"
#include <string>

class Node{
/*
		CLASS INVARIANTS: 
			1. data always points to a Data object
			2. next and previous always point to a Node or are NULL
*/
public:
  Node(WorkOrder newOrder);
    // Postcondition: next is set to NULL, a new Data object has been
    //	created with name = name and priorityLevel = priorityLevel
    
  Node* Next() const;
    // Precondition: next is NULL or points to a Node
    // Postcondition: value of next is returned
    
  const WorkOrder* Data() const;
    // Postcondition: return address of Data object 
    // (cannot be modified through the const pointer)
    
  void setNext(Node* newValue);
    // Postcondition: next has value of newValue
    
  ~Node();
    // Postcondition: Data object pointed to by data is deleted
    
private:
  WorkOrder* data; // the Node class manages allocation and deletion of WorkOrders 
  Node* next;  
};

#endif
