#include "customer.h"
/*

Class: Node

*/
class Node
{

public:
//pointer to a customer
    Customer* shopper;
//function returns address of next
    Node* getNext();
//function to set what next points to
    void setNext(Node* p);

private:
    Node* next;

};
