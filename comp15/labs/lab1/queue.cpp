// 
// queue.cpp
// Created by Aaron Tietz January 2012
//

#include <iostream>
#include "queue.h"
using namespace std;

/*  COPIED AND COMMENTED OUT HERE FOR EASY REFERENCE
struct Node{
  string value;
  Node* next;
};
*/

Queue::Queue(){
  front = NULL;
  back = NULL;
}

bool Queue::isEmpty() const
{
    
    if((front==NULL)&&(back==NULL))
	return true;
    else
	return false;
}

void Queue::add(string NewValue)
{
    if(isEmpty()==true)
    {
    Node* a=new Node;
    a->value=NewValue;
    a->next=NULL;
    front=a;
    }
    else
    {
    Node* a=new Node;
    a->value=NewValue;
    a->next=NULL;
    back=a;
    }
}

string Queue::remove()
{
   
    string deleted;

    if(isEmpty()==true)
	return "";
    else
    {
	Node* temp;
	temp=front;
	deleted=front->value;
	temp=front->next;
	delete front;
    }
    return deleted;
}

string Queue::getFront() const
{
  
    if(isEmpty()==true)
	return "";
    else
    {
	return front->value;
    }
}

void Queue::print() const
{
    
    Node* temp;
    temp=front;
    while(temp!=NULL)
    {
	cout << temp->value << endl;
	temp=temp->next;
    }
    
}
