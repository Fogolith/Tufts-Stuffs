//Jake Austin
//Comp15
//Project 3
//4/17/12
#include "Animal.h"


Animal::Animal(string a, int values[])
{
    name=a;
    for(int i=0; i<16; i++)
    {
	traits[i]=values[i];
    }
}

string Animal::getName()
{
    return name;
}

int Animal::getTrait(int a)
{
    int temp=traits[a];
    return temp;
}

//combine
//takes in two sets, returns third set with union of members
Set* Set::combine(Set comb1, Set comb2)
{
    Set* newSet=new Set;

    //add members from first set
    for(unsigned int i=0; i<comb1.members.size(); i++)
    {
	newSet->members.push_back(comb1.members[i]);
    }

    //add members from second set
    for(unsigned int i=0; i<comb2.members.size(); i++)
    {
	newSet->members.push_back(comb2.members[i]);
    }

    return newSet;
}
