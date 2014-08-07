#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StringSet
{
public:
//constructor 
    StringSet();
//produces a new set with intersection of a second set
    StringSet produceIntersection(StringSet* other);
//produces a new set with union of a second set
    StringSet produceUnion(StringSet* other);
//returns false if already present, otherwise adds new string to set
    bool add(string a);
//set company name, get company name
    void setName(string a);
    string getName();
//number of flavors
    int numFlavors;
    vector<string> flavors;//will be private 

private:

   
    string company;


};
