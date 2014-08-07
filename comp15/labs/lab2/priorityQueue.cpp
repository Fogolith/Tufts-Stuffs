// 
// priorityQueue.cpp
// Created by Aaron Tietz February 5, 2012
//

#include "priorityQueue.h"
#include "Node.h"
#include "WorkOrder.h"
#include <string>
#include <iostream>
using namespace std;

//priorityQueue()
// args: none 
// does: initializes front and back to NULL 
// calls: none 
// returns: none
priorityQueue::priorityQueue(){
 front = NULL;
}

//insertWithPriority()
// args: WorkOrder (copy of data for new Node)
// does: creates a new Node with a WorkOrder object of the values of newData
// 	and inserts the Node in the proper place in the queue based on the priority 
// 	of its WorkOrder object and the priorities of the WorkOrders of other Nodes.
// calls: ?
// returns: none   
void priorityQueue::insertWithPriority(WorkOrder newData)
{
    if(isEmpty()==true)
    {
	front=new Node(newData);
    }
    else
    {
	Node* temp=front;
	while(temp!=NULL)
	{
	    if(temp->Data()->PriorityLevel()>newData.PriorityLevel())
	    {
		if(temp->Next()==NULL)
		{
		    Node* p=new Node(newData);
		    temp->setNext(p);
		    return;
		}
		else if(temp->Next()->Data()->PriorityLevel()<newData.PriorityLevel())
		{
		    Node* p=new Node(newData);
		    p->setNext(temp->Next());
		    temp->setNext(p);
		    return;
		}
		
	    }
	    else if(temp->Data()->PriorityLevel()<newData.PriorityLevel())
	    {
		front=new Node(newData);
		front->setNext(temp);
		return;
	    }
	    temp=temp->Next();
	}
		    
    }
}

//removeHighestPriorityNode()
// args: none
// does: returns a copy of the WorkOrder object with highest priority in the queue
//	if queue is not empty
// calls: isEmpty()
// returns: if queue is empty, a WorkOrder object with name = "" and priorityLevel = 0.0
//  is returned, else a copy of the highest priority Node's WorkOrder object
WorkOrder priorityQueue::removeHighestPriorityNode()
{
    if(isEmpty())
    {
	WorkOrder temp("", 0.0);
	return temp;
    }
    else
    {
	WorkOrder temp(*(front->Data()));
	Node* temp1=front;
	front=front->Next();
	delete temp1;
	return temp;
    }

}

//isInQueue(string searchTerm)
// args: 1. string (string value to search for)
// does: searches queue for a WorkOrder object with name value equal to searchTerm
// calls: pqNode::getData(), pqNode::getNext(), pqData::getName()
// returns: true if searchTerm found, else false     
bool priorityQueue::isInQueue(string searchTerm) const{
    Node* temp=front;
    while(temp!=NULL)
    {
	if(temp->Data()->Name()==searchTerm)
	    return true;
	else
	{
	    temp=temp->Next();
	}
    }
    return false;

}

//removeFromQueue(string searchTerm)
// args: 1. string (value to remove from queue)
// does: 
// calls: isEmpty(), isInQueue(), 
// returns: number of Nodes removed
int priorityQueue::remove(string searchTerm){
  cout << "You still need to write removeFromQueue()\n";
  return 0;
}

//isEmpty()
// args: none
// does: determines if queue is empty or not empty 
// calls: none
// returns: true is queue is empty, else false 
bool priorityQueue::isEmpty() const{
  return(front == NULL);
}

//~priorityQueue()
// args: none 
// does: deletes any remaining pqNodes in the queue
// calls: none 
// returns: none 
priorityQueue::~priorityQueue(){
  cout << "You still need to write ~priorityQueue()\n";
}
