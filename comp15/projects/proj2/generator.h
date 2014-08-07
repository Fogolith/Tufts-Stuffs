#include "production.h"

class generator
{
private:
   vector<production> grammar;
   //main grammar structure, production made for each non terminal
   //at load in

public:
//constructor, not used
    generator();
//load in grammar from a file
    void load(string fname);
//generate a random sentence from grammar 
    string gen(string s);
//string to pass to gen in main as highest level grammar
    string sentence;

    
};
