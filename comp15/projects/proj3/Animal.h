//Jake Austin
//Comp15
//Project 3
//4/17/12
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

class Animal
{
public:

//constructor takes/sets animal name and traits
    Animal(string a, int values[]);

//getter for name
    string getName();

//getter for traits, takes index of trait
    int getTrait(int a);

private:

    string name;
    int traits[16];
};

class Set
{
public: 
      vector<Animal*> members;
      static Set* combine(Set comb1, Set comb2);

private:

};
