// Comp 15 Lab 6
// 
// main.cpp
// Run with 'allFiles' as your second command line argument (e.g. './a.out allFiles)

/*

FIRST CHALLENGE:

Remember:
1. Some files have duplicates - a rushed employee jotted down some flavors twice.
	We're creating sets, so make sure not to add duplicates.
	
2. You can create your StringSet class however you wish.  
	However, you must have these functions:

**Suggestion: change main to only read into one set first to make sure your class is working before 
  creating all eight **

// a set takes a reference to another set and produces 
//  a new set with the flavors they share
StringSet StringSet::produceIntersection(StringSet& other);

// a set takes a reference to another set and produces a 
// new set with all the unique flavors of their combined list.
// So, [vanilla, cherry] + [cherry, chocolate] would produce [vanilla, cherry, chocolate]
StringSet StringSet::produceUnion(StringSet& other);

// returns false if string is already in set, otherwise adds it and returns true
bool StringSet::add(string a);

SECOND CHALLENGE:
Show, for each ice cream company, 

1. Their biggest competitor (judged by largest intersection)
2. Their best merger option (judged by largest union - so, if they combined they'd have 
	the largest amount of unique flavors)
(write a function that prints 1 and 2 for all companies to the terminal)

3. Allow the user to enter a flavor and return the names of the companies, if any, 
	that sell that flavor 

THIRD CHALLENGE:

1. Use std::string.find() to implement flavor search with more results.  So, "mint"
would produce any flavor with mint in the name

// a set takes a reference to another set and produces a new set
//  that has the values contained in itself(or, *this), but not in other
2. StringSet StringSet::produceDifference(StringSet& other); 

3.  Think of how you could use string.find() to create a better union and intersection
	algorithm for the companies.  So, Mint Chip and Mint Chocolate Chip would be 
	considered the same thing. (you can write this function or pseudo-code function
	for a data set you don't have (e.g. "Mint Chocolate Chip" and not "mintchocolatechip")

http://www.cplusplus.com/reference/string/string/find/

*/





#include "StringSet.h"

int main(int Tufts, char** Jumbos){
  if(Tufts != 2){
    cerr << "To run type: './a.out allFiles' on the command line. \n";
    exit(1);
  }
  
  fstream files;
  cout << "Opening " << Jumbos[1] << endl;
  files.open(Jumbos[1]);
  if(!files){
    cerr << "Error opening " << Jumbos[1] << endl;
    exit(1);
  }
  
  
  fstream data;
  string fileName;
  string newString;

  vector<StringSet> companys;

  while(files >> fileName){
      
    // for each new file, you'll be adding strings to a new set
  
    // open a new file
    cout << "Opening: " << fileName << endl;
    data.open(fileName.c_str());
    if(!data){
      cerr << "Error opening " << fileName << endl;
      exit(1);
    }
    int iter=0;
    StringSet temp;
    // go through the file
    while(data >> newString)
    {
      for(int j = 0; j < newString.length(); ++j){
        newString[j] = tolower(newString[j]);
      }
    	cout << newString << endl;
	if(iter==0)
	    temp.setName(newString);
	else
	    bool a=temp.add(newString);
	iter++;
	
    }
    cout << iter << endl;
    temp.numFlavors=(iter-1);
    cout << temp.numFlavors << endl;
    companys.push_back(temp);
    // close the connection so that you can open a new one with the next file
    data.close();
    cout << endl << endl;
  }  

  // close your connection to the file of file names
  files.close();  

  StringSet inter=companys[0].produceIntersection(&companys[1]);

  for(int i=0; i<inter.numFlavors; i++)
  {
      cout << inter.flavors[i] << endl;
  }
  return 0;
}


