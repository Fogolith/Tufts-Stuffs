#include "supermarket.h"

int main()
{
    Supermarket* myStore=new Supermarket();

    cout << "Enter Configuration (1-4): ";
    int config;
    cin >> config;

    string fname;
    cout << "Enter Customer file name: ";
    cin >> fname;
    cout << endl << endl;
    Queue* a=myStore->pool;
    myStore->load(fname);
    myStore->pool=myStore->mergeSort(a);
    a=myStore->pool;
    myStore->print(a);
/*
    if(config==1)
	myStore->run_sim();
    else if(config==2)
	myStore->run_sim2();
    else if(config==3)
	myStore->run_sim3();
    else if(config==4)
	myStore->run_sim4();
    else if((config<1)||(config>4))
	cout <<"Invalid Configuration" << endl;
*/
    return 0;
}


