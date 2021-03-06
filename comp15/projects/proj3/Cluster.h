//Jake Austin
//Comp15
//Project 3
//4/17/12
#include "Animal.h"

class Cluster
{

public:
//constructor
    Cluster();
//vector of sets of animals
    vector<Set*> allSets;

//read in datafile, store in allSets
    void loadAnimals();

//calculates most related pair of sets, combines them
    void mergeClosest();

//calculates maximum distance between two members of two sets
    double distMax(Set test1, Set test2);

//calculates minimum distance between two members of two sets
    double distMin(Set test1, Set test2);

//calculates the average distance between members of two sets
    double distAvg(Set test1, Set test2); 

//set final number of clusters
    void setStop(int stop);

//get final number of clusters
    int getStop();

//set file name
    void setfName(string name);

//set which distance metric is to be used
    void setMetric(int Metric);

//return distance metric
    int getMetric();

//print final clusters
    void print();

//find greatest number of legs of any animal
    void mostLegs();

private:
//int for final number of clusters
    int stopClustering;

//int representing which distance metric to use (1=min, 2=max, 3=avg)
    int metric;

//file name
    string fName;

//int for greatest number of legs of any animal
    int legs;
};
