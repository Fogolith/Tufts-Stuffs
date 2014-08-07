//Jake Austin
//Comp15
//Project 3
//4/17/12
#include "Cluster.h"

Cluster::Cluster()
{
    string fName="";
}
 
void Cluster::setStop(int stop)
{
    stopClustering=stop;
}

int Cluster::getStop()
{
    return stopClustering;
}

void Cluster::setfName(string name)
{
    fName=name;
}

void Cluster::setMetric(int Metric)
{
    metric=Metric;
}

int Cluster::getMetric()
{
    return metric;
}

//calculates greatest number of legs of any animal
//#legs will be divided by greatest number to make #legs trait range 0-1,
//balancing it with other traits
void Cluster::mostLegs()
{
    int most=0;
    for(unsigned int i=0; i<allSets.size(); i++)
    {
	if(allSets[i]->members[0]->getTrait(12)>most)
	{
	    most=allSets[i]->members[0]->getTrait(12);
	}
    }
    legs=most;
   
}

//creates new set with 1 new animal for each animal read in, stores all in 
//allSets
void Cluster::loadAnimals()
{
    ifstream fin;
    fin.open(fName.c_str());
    string name="";
    int traits[16];
    while(!fin.eof())
    {
	fin >> name;
	if(!fin.eof())
	{
	    for(int i=0; i<16; i++)
	    {
		fin >> traits[i];
	    }
            Animal* temp=new Animal(name, traits);
	    Set* tempSet=new Set;
	    tempSet->members.push_back(temp);
	    allSets.push_back(tempSet);
	}
    }
}

void Cluster::print()
{
    for(unsigned int i=0; i<allSets.size(); i++)
    {	
	cout << "Cluster " << i << endl;
	for(unsigned int k=0; k<allSets[i]->members.size(); k++)
	{
	    cout << "   " << allSets[i]->members[k]->getName() << endl;
	}
	cout << endl;
    }
}

//Calculates the maximum distance between pairs of members of two sets
double Cluster::distMax(Set test1, Set test2)
{
    Animal* close1;
    Animal* close2;
    double maxDist=-1;

    double total;
    for(unsigned int i=0; i<test1.members.size(); i++)
    {//reads through members of first set
 	for(unsigned int k=0; k<test2.members.size(); k++)
	{//compares to all members of second set
	    for(int j=0; j<16; j++)
	    {//compares all traits
		if(j==12)//balancing #legs with other traits
		{
		    double a=((test1.members[i]->getTrait(j))/legs);
		    double b=((test2.members[k]->getTrait(j))/legs);
		    double c=(a-b);
		    total+=(c*c);
		}
			    	    
		if(j!=12)
		{
		    double a=(test1.members[i]->getTrait(j)-test2.members[k]->getTrait(j));
		    total+=(a*a);
		}
	    }
	    total=sqrt(total);
	    if(maxDist==-1)//set first
	    {
	        maxDist=total;
	        close1=test1.members[i];
	        close2=test2.members[k];
	    }
	    else if(total>maxDist)//checks for pairs of animals
	    {
	        maxDist=total;
	        close1=test1.members[i];
	        close2=test2.members[k];
	    }
	}
    }
    return total;
}

//Calculates the minimum distance between pairs of members of two sets
double Cluster::distMin(Set test1, Set test2)
{
    Animal* close1;
    Animal* close2;
    double minDist=-1;

    double total;
    for(unsigned int i=0; i<test1.members.size(); i++)
    {
 	for(unsigned int k=0; k<test2.members.size(); k++)
	{
	    for(int j=0; j<16; j++)
	    {
		if(j==12)//balancing #legs with other traits
		{
		    double a=((test1.members[i]->getTrait(j))/legs);
		    double b=((test2.members[k]->getTrait(j))/legs);
		    double c=(a-b);
		    total+=(c*c);
		}
			    	    
		if(j!=12)
		{
		    double a=(test1.members[i]->getTrait(j)-test2.members[k]->getTrait(j));
		    total+=(a*a);
		}
		
	    }
	    total=sqrt(total);
	    if(minDist==-1)
	    {
		minDist=total;
		close1=test1.members[i];
		close2=test2.members[k];
	    }
	    else if(total<minDist)
	    {
		minDist=total;
        	close1=test1.members[i];
	        close2=test2.members[k];
	    }
	}
    }
    return total;
}

//Calculates average distance between ALL pairs of members of two sets
double Cluster::distAvg(Set test1, Set test2)
{
    vector<double> distances;//vector for distances between all pairs

    double total;
    double average;
    for(unsigned int i=0; i<test1.members.size(); i++)
    {
 	for(unsigned int k=0; k<test2.members.size(); k++)
	{
	    for(int j=0; j<16; j++)
	    {
	        if(j==12)//balancing #legs with other traits
		{
		    double a=((test1.members[i]->getTrait(j))/legs);
		    double b=((test2.members[k]->getTrait(j))/legs);
		    double c=(a-b);
		    total+=(c*c);
		}
			    	    
		if(j!=12)
		{
		    double a=(test1.members[i]->getTrait(j)-test2.members[k]->getTrait(j));
		    total+=(a*a);
		}
	    }	
	    total=sqrt(total);
	    distances.push_back(total);
	}
    }
    for(unsigned int i=0; i<distances.size(); i++)
    {
	average+=distances[i];
    }
    average=(average/distances.size());
    return average;
}

//finds pair of sets with shortest distance, merges into a single new set, 
//stores new set and deletes old sets
void Cluster::mergeClosest()
{
    double shortest=-1;
    double test=-1;
    int merge1=-1;
    int merge2=-1;

    for(unsigned int i=0; i<allSets.size(); i++)//reads through all sets
    {
	for(unsigned int j=(i+1); j<allSets.size(); j++)//compares to following
	{
	    if(getMetric()==1)//calls minimum function
	    {		      //runs comparison on all possible pairs
		test=distMin(*allSets[i], *allSets[j]);
		if(shortest==-1)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
		if(test<shortest)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
	    }
	    else if(getMetric()==2)//calls maximum function
	    {			   //runs comparison on all possible pairs
		test=distMax(*allSets[i], *allSets[j]);
		if(shortest==-1)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
		if(test<shortest)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
	    }
	    else if(getMetric()==3)//calls average function
	    {			   //runs on all possible pairs
		test=distAvg(*allSets[i], *allSets[j]);
		if(shortest==-1)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
		if(test<shortest)
		{
		    shortest=test;
		    merge1=i;
		    merge2=j;
		}
	    }
	}
    }
//merge the two sets that produce the shortest distance
    Set* adding=Set::combine(*allSets[merge1], *allSets[merge2]);
//add new set to main vector of sets
    allSets.push_back(adding);
//deletes the two sets that were combined from the array
    if(merge1>merge2)
    {
        allSets.erase(allSets.begin()+merge1);
        allSets.erase(allSets.begin()+merge2);
    }
    else
    {
        allSets.erase(allSets.begin()+merge2);
        allSets.erase(allSets.begin()+merge1);
    }
}
