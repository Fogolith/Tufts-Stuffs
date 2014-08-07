#include "TrigVector.h"
#include "Language.h"

class Analyzer
{

public:

    Analyzer();
    //Constructor, initializes class member values

    void run();
    //Manages programs functions

private:
  
    Language* langList;
    //array for different languages

    int LSIZE;
    //size of language array
    
    int languageCount;
    //associated counter

    TrigVector* unknowns;
    //array for unknown docs

    int USIZE;
    //size of unknown array

    int unknownCount;
    //associated counter

    void readIn();
    //reads in master file, stores documents of the same 
    //language in appropriate index of language array 
    //stores unknowns in unknown array

    void process();
    //Calls the Language/TrigVector processing functions

    double compare(Language a, TrigVector b);
    //compares a document to a language, returns 0-99 probability of identity

    void printResults();
    //Calls comparing function and prints results

};
