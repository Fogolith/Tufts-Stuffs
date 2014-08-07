#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

//a 'rule' is a set of strings that compose a production rule.
//eg. the vector of rules for sentence would have "NP" and "VP" as the two
//strings in the first index of a vector of rules 
struct rule
{
    vector<string> pieces;
};

//a 'production' has some non-terminal "NT", a vector of rules for multiple
//production endings, and a vector of strings for terminal values 
struct production
{
    string NT;
    vector<string> words;
    vector<rule> rules;
    bool hasLeaves;
};
