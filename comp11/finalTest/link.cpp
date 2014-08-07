#include <iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

struct Node
{
    int w;
    int x;
    int y;
   
    Node* next;
};

int main()
{  
    int Size;
    cout << "How many #s of the Fibonacci sequence would you like?" << endl;
    cin >> Size;
	int counter=Size;
	Node* Poop;
	Poop=new Node;
	Poop[0]->next=NULL;
	Poop[0]->w=0;
	Poop[0]->x=0;
	Poop[0]->y=1;
	
	
	Poop[1]->w=0;
	Poop[1]->x=1;
	Poop[1]->y=1;
	while(counter>=0)
	{
	    Poop[counter]->w=Poop[counter]->x;
	    Poop[counter]->x=Poop[counter]->y;
	    Poop[counter]->y=((Poop[counter]->w)+(Poop[counter]->x));
	   
	    Poop[counter-1]->next=new Node;
	    Poop[counter]->next=Poop[counter-1];
	    counter--;
	}
	Node* iter=Poop[Size];
	while(iter!=NULL)
	{
	    cout << iter->y << " ";
	    iter=iter->next;
	}
	return 0;
}
