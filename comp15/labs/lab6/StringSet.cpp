#include "StringSet.h"

StringSet::StringSet()
{
    company="";
    numFlavors=0;
}

StringSet StringSet::produceIntersection(StringSet* other)
{
    StringSet inter;
    for(int i=0; i<numFlavors; i++)
    {
	for(int j=0; j<other->numFlavors; j++)
	{
	    
	    if(flavors[i]==other->flavors[j])
	    {
		inter.add(flavors[i]);
		inter.numFlavors++;
	    
	    }
	    
	}
    }
    cout << "returning" << endl;
    return inter;

}

StringSet StringSet::produceUnion(StringSet* other)
{

}

void StringSet::setName(string a)
{
    company=a;
}
string StringSet::getName()
{
    return company;
}

bool StringSet::add(string a)
{
    for(int i=0; i<flavors.size(); i++)
    {
	if(a==flavors[i])
	    return false;
    }
    flavors.push_back(a);
    return true;
}
