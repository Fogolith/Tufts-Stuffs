#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

class Animal
{
public:
    Animal(string a, vector<int> values);

    string getName();

    int getTrait(int a);

friend bool operator>(const Animal &first, const Animal &second){
return(first.name > second.name);
}

friend bool operator==(const Animal &first, const Animal& second){
return(first.name == second.name);
}

friend bool operator<(const Animal &first, const Animal &second){
    return(first.name<second.name);
}

private:

    string name;
    int traits[16];

};
