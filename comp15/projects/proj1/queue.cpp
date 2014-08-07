#include "queue.h"

//Cunstructor, initializes pointers and length of queue
Queue::Queue()
{
    front=NULL;
    checkingOut=NULL;
    back=NULL;
    length=0;
}

//Returns bool if queue (excluding checkingOut)
bool Queue::isEmpty()
{
    return(front==NULL);
}

//ADD
//Argument:    Customer*
//Returns:     Nothing
//Creates new node for incoming customer
void Queue::add(Customer* c)
{
    if(isEmpty())//adds new node at front
    {
        front=new Node;
	front->shopper=c;
	front->setNext(NULL);
	back=front;
	length+=1;	   
    }
    else
    {
	Node* temp=new Node;
	temp->shopper=c;
	temp->setNext(NULL);
	length+=1;
	back->setNext(temp);
	back=temp;
    }
}

//REMOVE
//Argument    Time(from supermarket)
//Returns     Nothing
//resets front and delets old Node, assigns customer at front to checkingOut
void Queue::remove(int time)
{
    if(checkingOut==NULL)//Only if register is available
    {
	if(front!=NULL)//only if a customer is waiting at front of queue
	{
            checkingOut=front->shopper;
            checkingOut->setCheckOUT(time);
            Node* temp=front;
            front=front->getNext();
            delete temp; 
	     
	}
    }  
}

//CHECKOUT
//Argument    Time(from supermarket)
//Returns     bool(that a customer has checkedOut)
//prints customers information when they have finished time at register
bool Queue::checkOut(int time)
{
    if(checkingOut!=NULL)
    {//if they have been at the register for as many seconds as they have items
    	if(time==(checkingOut->getItems()+checkingOut->getCheckOUT()))
    	{
	        checkingOut->print();
                length-=1;
		delete checkingOut;
        	checkingOut=NULL;//opens register
		return true;
    	}
    }
    return false;
}

//Returns address of front node
Node* Queue::inFront()
{
    return front;
}

//Setter for front pointer
void Queue::setFront(Node* a)
{
    front=a;
}

//returns address of paying customer
Customer* Queue::isCheckingOut()
{
    return checkingOut;
}

//set Customer* checkingOut
void Queue::setCheckingOut(Customer* c)
{
    checkingOut=c;
}

//Returns private data member: length
int Queue::getLength()
{
    return length;
}
