#include "node.h"
#include "customer.h"

/*

class Queue

Private pointers to manage Nodes, and associated queue functions
*/

class Queue
{

public:
//default constructor
    Queue();

//add a customer to the back of the queue
    void add(Customer* c);

//remove a customer from the front of the line to checkout
    void remove(int time);

//remove customer from supermarket when done checking out, prints info
    bool checkOut(int time);

//return address of front customer (not remove them)
    Node* inFront();

//return address of paying customer
    Customer* isCheckingOut();

//set customer at register without using remove function
//--only used in bank simulation to use register and avoid going through queues
    void setCheckingOut(Customer* c);

//change where front points
    void setFront(Node* a);

//return true if queue is empty
    bool isEmpty();

//returns length (number of nodes/customers in) of queue
    int getLength();

private:
    
//length of (number of customers in) queue
    int length;
//pointer to customer in front of line (first node)
    Node* front;
//pointer to customer at back of line(back->getNext=NULL)
    Node* back;
//pointer to customer on register (holding outside queue before checkout)
    Customer* checkingOut;
};
