#include "supermarket.h"
#include <fstream>

Queue* Supermarket::mergeSort(Queue* toBeSorted)
{
    Queue one;
    Queue two;

    Node* temp=toBeSorted->inFront();
    if(toBeSorted->getLength()==1)
    {
        return toBeSorted;
    }
    while(temp!=NULL)
    {
	one.add(temp->shopper);
	temp=temp->getNext();
	if(temp!=NULL)
	{
	    two.add(temp->shopper);
	    temp=temp->getNext();
	}
    }
    
    Queue* catch1=mergeSort(&one);
    Queue* catch2=mergeSort(&two);
    
    toBeSorted=combine(catch1, catch2);
    return toBeSorted;
}
Queue* Supermarket::combine(Queue* one, Queue* two)
{
    Queue three;
    Node* temp=one->inFront();
    Node* temp2=two->inFront();
    while((temp!=NULL)||(temp2!=NULL))
    {
	if(temp==NULL)
	{
	    three.add(temp2->shopper);
	    temp2=temp2->getNext();
	}
	if(temp2==NULL)
	{
	    three.add(temp->shopper);
	    temp=temp->getNext();
	}
        if(temp->shopper->getItems()>=temp2->shopper->getItems())
        {   
	    three.add(temp2->shopper);
	    temp2=temp2->getNext();
        }
        else  
        {
	    three.add(temp->shopper);
	    temp=temp->getNext();
	}
	
    }
    return three;
}

void Supermarket::print(Queue* getPrint)
{
    Node* temp=getPrint->inFront();
    while(temp!=NULL)
    {
	cout << temp->shopper->getItems() << "      ";
	temp=temp->getNext();
    }
}
//Constructor, initializes holding queue, time, numCheckedOut
Supermarket::Supermarket()
{   
    time=0;
    numCheckedOut=0;
    pool=new Queue;
}

//LOAD
//Argument    fname (filename entered by user)
//Returns     Nothing
//Takes in filename, loads customers into holding queue, sets numCustomers
void Supermarket::load(string fname)
{
    ifstream fin;
    fin.open(fname.c_str());

    string name;
    int items;
    int arrival;

    while(!fin.eof())
    {
        fin >> name >> items >> arrival;
	if(!fin.eof())
	{
	    Customer* temp=new Customer;
	    temp->setName(name);
	    temp->setItems(items);
	    temp->setCheckIN(arrival);
	    pool->add(temp);
	    numCustomers++;
        }
    }  
}

//RUN_SIM
//Argument    Nothing
//Returns     Nothing
//moves arriving customers from pool to line, checks out customers, moves
//waiting front customer to checkout
void Supermarket::run_sim()
{
    Queue line;
    while(numCustomers!=numCheckedOut)
    {
	Node* temp=pool->inFront();

	while(temp!=NULL)//iterates through pool
	{
	    if(time==temp->shopper->getCheckIN())//when time==arrival
	    {
		pool->setFront(pool->inFront()->getNext());
		line.add(temp->shopper);
		delete temp;
		temp=pool->inFront();
	    }
	    else
		temp=temp->getNext();
	}

	if(line.checkOut(time))//returns if a customer checked out, opens checkout
	    numCheckedOut++;

	line.remove(time);//moves customer from front to checkout if empty

	time++;
    }
}

//GET SHORTEST
//Argument:    pointers to each of the 4 queues
//Returns:     pointer to queue with lowest length value	
Queue* Supermarket::getShortest(Queue* a, Queue* b, Queue* c, Queue* d)
{
    if(a->getLength()<=b->getLength())
	if(a->getLength()<=c->getLength())
	    if(a->getLength()<=d->getLength())
		return a;

    if(b->getLength()<=c->getLength())
	if(b->getLength()<=d->getLength())
	    return b;

    if(c->getLength()<=d->getLength())
	return c;
    
        return d;
    
}

//RUN_SIM2
//Added:    getShortest call to assign customer to shortest queue, queues run in parallel
void Supermarket::run_sim2()
{
    Queue line1;
    Queue line2;
    Queue line3;
    Queue line4;

    Queue* L1=&line1;
    Queue* L2=&line2;
    Queue* L3=&line3;
    Queue* L4=&line4;

    while(numCustomers!=numCheckedOut)
    {
        Node* temp=pool->inFront();     

        while(temp!=NULL)
        {
	    if(time==temp->shopper->getCheckIN())
            {
	        pool->setFront(pool->inFront()->getNext());
		getShortest(L1,L2,L3,L4)->add(temp->shopper);
                delete temp;
                temp=pool->inFront();
            }
            else
	        temp=temp->getNext();
        }

        if(line1.checkOut(time))
            numCheckedOut++;
	if(line2.checkOut(time))
            numCheckedOut++;
	if(line3.checkOut(time))
            numCheckedOut++;
	if(line4.checkOut(time))
            numCheckedOut++;

	line1.remove(time);
	line2.remove(time);
	line3.remove(time);
	line4.remove(time);

        time++;
    }
}

//RUN_SIM3
//Added:   conditional to serparate express/nonexpress customers 
void Supermarket::run_sim3()
{
    Queue line1;	
    Queue line2;
    Queue line3;	//Queues 3&4 are non-express queues
    Queue line4;

    Queue* L1=&line1;
    Queue* L2=&line2;
    Queue* L3=&line3;
    Queue* L4=&line4;

    while(numCustomers!=numCheckedOut)
    {
        Node* temp=pool->inFront();
       

        while(temp!=NULL)
        {
	    if(time==temp->shopper->getCheckIN())
            {
	        pool->setFront(pool->inFront()->getNext());
		if(temp->shopper->isExpress==false)	//if not express, one or two
		{
		    if(line3.getLength()<=line4.getLength())
			line3.add(temp->shopper);
		    else if(line4.getLength()<line3.getLength())
			line4.add(temp->shopper);
		}
		else if(temp->shopper->isExpress==true)	//if express, shortest
		    getShortest(L1,L2,L3,L4)->add(temp->shopper);

                delete temp;
                temp=pool->inFront();
            }
            else
	        temp=temp->getNext();
        }

        if(line1.checkOut(time))
            numCheckedOut++;
	if(line2.checkOut(time))
            numCheckedOut++;
	if(line3.checkOut(time))
            numCheckedOut++;
	if(line4.checkOut(time))
            numCheckedOut++;

	line1.remove(time);
	line2.remove(time);
	line3.remove(time);
	line4.remove(time);

            time++;
    }
}

//RUN_SIM4
//1 line, 4 registers
//uses 3 queues only for registers (never adds customers to linked list)
//
void Supermarket::run_sim4()
{
    Queue line;
    Queue register2;
    Queue register3;
    Queue register4;
   
    while(numCustomers!=numCheckedOut)
    {
        Node* temp=pool->inFront();
      
	while(temp!=NULL)//iterates through pool
	{
	    if(time==temp->shopper->getCheckIN())//when time==arrival
	    {
		pool->setFront(pool->inFront()->getNext());
		line.add(temp->shopper);
		delete temp;
		temp=pool->inFront();
	    }
	    else
		temp=temp->getNext(); 
	      
	}
	
	if(line.checkOut(time))//returns if a customer checked out
	    numCheckedOut++;
	if(register2.checkOut(time))
	    numCheckedOut++;
	if(register3.checkOut(time))
	    numCheckedOut++;
	if(register4.checkOut(time))
	    numCheckedOut++;

	line.remove(time);

/*
Hard coded a remove function to move customers from line to DIFFERENT Queue's
register. 
*/
	if((register2.isCheckingOut()==NULL)&&(line.inFront()!=NULL))
	{
	    register2.setCheckingOut(line.inFront()->shopper);
	    register2.isCheckingOut()->setCheckOUT(time);
	    Node* temp=line.inFront();
	    line.setFront(line.inFront()->getNext());
	    delete temp;
	}
	if((register3.isCheckingOut()==NULL)&&(line.inFront()!=NULL))
	{
	    register3.setCheckingOut(line.inFront()->shopper);
	    register3.isCheckingOut()->setCheckOUT(time);
	    Node* temp=line.inFront();
	    line.setFront(line.inFront()->getNext());
	    delete temp;
	}
       	if((register4.isCheckingOut()==NULL)&&(line.inFront()!=NULL))
	{
	    register4.setCheckingOut(line.inFront()->shopper);
	    register4.isCheckingOut()->setCheckOUT(time);
	    Node* temp=line.inFront();
	    line.setFront(line.inFront()->getNext());
	    delete temp;
	}
	time++; 
    } 
}

