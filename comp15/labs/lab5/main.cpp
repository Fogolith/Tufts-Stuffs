//
// main.cpp
//

#include <iostream>
#include "BST.h"
#include <cstdlib>
#include <fstream>
using namespace std;

const int SECOND_MEMBER_OF_COMMAND_LINE_ARGUMENT_ARRAY = 1;

int main(int numberOfCommandLineArguments, char* argumentsAsAnArrayOfCStrings[]){
  
  if(numberOfCommandLineArguments != 2){
    cerr << "Run program with an input file name, e.g.: './a.out inputFile.txt'\n"; 
    exit(1);
  }
  
  ifstream fileInput;  
  fileInput.open(argumentsAsAnArrayOfCStrings[SECOND_MEMBER_OF_COMMAND_LINE_ARGUMENT_ARRAY]);
  if(!fileInput){
    cerr << "Problem opening input file " 
         << argumentsAsAnArrayOfCStrings[SECOND_MEMBER_OF_COMMAND_LINE_ARGUMENT_ARRAY] 
         << endl;
    exit(1);
  }
  
  BST tree;
  string word;
  while(fileInput >> word){
    tree.insert(word); 
  }
  
  cout << "PreOrder:\n";
  tree.printPreOrderTraversal();
  cout << endl << endl;
  
  cout << "PostOrder:\n";
  tree.printPostOrderTraversal();
  cout << endl << endl;
  
  cout << "InOrder:\n";
  tree.printInOrderTraversal();
  cout << endl << endl;
  
  cout << "Size: " << tree.size() << endl;
  cout << "Height: " << tree.height() << endl;

  if(tree.find("Apple"))
      cout << "yep!" << endl;

  if(tree.find("poop"))
      cout << "what?!" << endl;
  
  return 0;
}
