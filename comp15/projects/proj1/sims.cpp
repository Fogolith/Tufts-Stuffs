/*   

need to add getShortest function to supermarket class(compares queue's for shortest wait time [config 2-3])
create multiple run_sim functions based on configuration?

void Supermarket::run_sim2()
{
    queue line1;
    queue line2;
    queue line3;
    queue line4;

    while(numCustomers!=numCheckedOut)
    {
        Node* temp=pool->inFront();
       

        while(temp!=NULL)
        {
	    if(time==temp->shopper->getArrival())
            {
	        pool->setFront(pool->inFrint()->getNext());
                getShortest()->add(temp->shopper);                   //GETSHORTEST
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
  


void Supermarket::run_sim3()
{
    queue line1;         //1&2 are not express, 3&4 are
    queue line2;
    queue line3;
    queue line4;

    while(numCustomers!=numCheckedOut)
    {
        Node* temp=pool->inFront();
        

        while(temp!=NULL)
        {
	    if(time==temp->shopper->getArrival())
            {
	        pool->setFront(pool->inFrint()->getNext());
                if(temp->shopper->isExpress==false)
                {
		    if(line1.getLength()>line2.getLength())
		        line2.add(temp->shopper); 
		    else
		        line1.add(temp->shopper);    
                }
                else
                {
		    getShortest()->add(temp->shopper);                   //GETSHORTEST      
                }
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
                      

*/
