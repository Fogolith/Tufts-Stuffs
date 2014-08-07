/*

Class: CUSTOMER

Private data members for customer info and associated functions 
	-Name
	-#Items (isExpress)
	-Time-in line
	-Time-out line
	
*/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#ifndef JAKE_CUSTOMER_H
#define JAKE_CUSTOMER_H

class Customer
{

public:
//bool for exprss lane pass (<5 items)
    bool isExpress;
//default constructor
    Customer();
//set name at load in
    void setName(string newName);
//return customer name 
    string getName();
//set numItems at load in, also determines if customer is express or not
    void setItems(int num);
//return numItems
    int getItems();
//set arrival time at load in
    void setCheckIN(int num);
//return checkIN
    int getCheckIN();
//set checkout time when removed from queue
    void setCheckOUT(int num);
//return checkOUT
    int getCheckOUT();
//print info when removed from checkout
    void print();
   

private:
//customer name
    string name;
//item count
    int numItems;
//arrival time
    int checkIN;
//checkout time (end of wait time)
    int checkOUT;

};

#endif
