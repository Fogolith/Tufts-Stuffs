// Aaron Tietz
// Comp 15 Spring 2012
// Lab 7/8
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Animal.h"
using namespace std;

struct Node{
  Animal* data;
  Node* next;
  Node(Animal* a){
    data = a;
    next = NULL;
  }
};

// hash takes a pointer to an Animal and does a calculation
// on the name of the Animal to produce an int between 0
// and arraySize -1
int hash(string a, int arraySize);

// adds Animal* to the array by making a new Node and putting it either 
// at the head of the list or the end, depending on whether or not
// something is already there
void addToArray(Animal *a, int location, Node** theArray);

int collisionCount = 0;

// returns the number of items with given string found
// in theArray using the hash function you wrote in hash()
int findCountWithHash(string toFind, int arraySize, Node** theArray);

int main(int argumentCount, char** arguments){
  if(argumentCount != 2){
    cerr << "Command line usage: ./a.out [int - size of hash table]" << endl;
    exit(1);
  }

  fstream input;
  input.open("zoo2.data");
  if(!input){
    cerr << "Couldn't find zoo2.data file in current directory\n";
    exit(1);
  }
  
  string name;
  int temp;
  vector<int> traits;
  // argument[1] is the second command line argument, and 
  // atoi() converts it into an integer from a character array
  Node** zoo = new Node*[atoi(arguments[1])];
  
  int sizeOfArray = atoi(arguments[1]);
  for(int i = 0; i < sizeOfArray; i++)
    zoo[i] = NULL;
 
  
  while(input >> name){
    for(int i = 0; i < 16; ++i){
      input >> temp;
      traits.push_back(temp);
    }
    
    Animal* a = new Animal(name, traits);
    if(a != NULL){
      // the second argument of addToArray() is an int, which 
      // is what hash(name, sizeOfArray) returns
      addToArray(a, hash(name, sizeOfArray), zoo);
    }
    
    traits.clear();
  }
  
  string toFind = "";
  
  cout << "Enter the name of an animal to find, or x to quit\n";
  cin >> toFind;
  while(toFind != "x"){
    cout << findCountWithHash(toFind, sizeOfArray, zoo) << toFind << "(s) was/were found\n";
    cout << "Enter the name of an animal to find, or x to quit\n";
    cin >> toFind;
  }
  
  cout << "Total collisions for array of size " << sizeOfArray 
  	<< " with 101 animals, using your current hash(): " << collisionCount << endl;
    
  return 0;
}




/*
  As you try out different hash functions today, test them on 
  arrays of a few sizes, then save them by commenting them out -
  it would be nice if you wrote down their results and saved that
  in the comment, then tested the other algorithms you wrote using
  the same array sizes to do a comparison.
*/

// hash takes a pointer to an Animal and does a calculation
// on the name of the Animal to produce an int between 0
// and arraySize -1
int hash(string data, int arraySize){

    return((data[0]*223)%arraySize);

}

// adds Animal* to the array by making a new Node and putting it either 
// at the head of the list or the end, depending on whether or not
// something is already there
void addToArray(Animal *a, int location, Node** theArray){
	
	//if you find something in the array location
	// collisionCount++ (just once, not once for each
	// Node at that location)
    Node* temp=new Node(a);
    if(theArray[location]==NULL)
    {
	theArray[location]=temp;
    }
    else 
    {
        Node* iter=theArray[location];
	collisionCount++;
	while(iter->next!=NULL)
	{
	    iter=iter->next;
	}
	iter->next=temp;

    }
	//Note: I intentionally removed the extra frog and 
	// copied and repasted the last five entries on zoo.data
	// to make zoo.data2 to make sure you'd at least have 
	// a few collisions to have to deal with
}


// returns the number of items with given string found in theArray 
int findCountWithHash(string toFind, int arraySize, Node** theArray){
  
  int count=0;
  int location = hash(toFind, arraySize);
  Node* iter=theArray[location];
  while(iter!=NULL)
  {
      if(iter->data->getName()==toFind)
      {
	  count++;
      }
      iter=iter->next;
  }

  return count;
}
