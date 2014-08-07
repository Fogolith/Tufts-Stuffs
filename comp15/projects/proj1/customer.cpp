#include "customer.h"

//Default cunstructor, initializes a blank customer 
Customer::Customer()
{

    name="";
    numItems=-1;
    isExpress=false;
    checkIN=-1;
    checkOUT=-1;
}

//Setter for private data member: name
void Customer::setName(string newName)
{
    name=newName;
}

//Getter
string Customer::getName()
{
    return name;
}

//Setter for private data member: numItems, Sets isExpress
void Customer::setItems(int num)
{
    numItems=num;
    if(numItems<=5)		
	isExpress=true;
}

//Getter
int Customer::getItems()
{
    return numItems;
}

//Setter for private data member: checkIN (time entering queue)
void Customer::setCheckIN(int num)
{
    checkIN=num;
}

//Getter
int Customer::getCheckIN()
{
    return checkIN;
}

//Setter for private data member: checkOUT (time leaving queue)
void Customer::setCheckOUT(int num)
{
    checkOUT=num;
}

//Getter
int Customer::getCheckOUT()
{
    return checkOUT;
}

//Prints customer data when customer checks out of register.
void Customer::print()
{
    cout << name << " " << numItems << " " << checkIN << " ";
    cout << (checkOUT-checkIN) << endl;
}
