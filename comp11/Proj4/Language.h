#include "TrigVector.h"
#include "TrigInfoSTR.h"

/*

Class Definition of Language

Language is a collection of TrigVectors (documents) of the same language type.
It has functions for aggregating the TrigInfo arrays from its TrigVectors,
and its own function for determining the frequencies of its TrigInfo array.

*/

class Language
{

public:

    Language();
    //Constructor, initializes values for class members

    void processLang();
    //Calls all language-level processing functions

    string language;
    //for identification

    TrigVector* docs;
    //array of TrigVectors associated with this language (docs)

    int vectSize;
    //size of TrigVector array

    int vectorCount;
    //# of documents readIn of language type

    TrigInfo* aggregate;
    //array for the compounded trigram info

    int numberTrigs;
    //number of trigrams for the whole language  

private:
 
    int trigSize;
    //size of trigram array

    int consolidate();
    //function that adds up all TrigInfo arrays from docs into aggregate

    void Lfrequelizer();
    //calculates/stores frequencies in aggregate array    

};
