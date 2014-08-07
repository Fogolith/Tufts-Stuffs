#ifndef TrigVectorCLS
#define TrigVectorCLS
#include "TrigInfoSTR.h"

/*

Class Definition of TrigVector

TrigVector represents an individual document. It contains functions for 
reading in the document with a filestream, processing the text, creating
trigrams, and storing statistics about those trigrams.  

*/

class TrigVector
{

public:

    TrigVector();
    //Constructor, sets values for arrays and class members

    void processDocs();
    //runs all TrigVector functions

    string language;
    //for identification, read in from master file

    string fName;
    //name of associated file (also read in)

    TrigInfo* trigList;
    //array for trigrams/counters/frequencies

    int numberTrigs;
    //# of unique trigrams for document

   

private:

    string readFile();
    //reads in file, cleans out punctuation and returns 'text'

    string cleanUp();
    //reads in text, cleans multiple spaces and returns 'text'

    string text;
    //edited, ready-to-trigram text

    int Trigrammer();
    //reads text and creates/stores  associated trigrams/counters 
    //returns numberTrigs

    void frequelizer();
    //calculates and stores frequency for all trigrams in trigList

    int trigSize;
    //size of trigList
  

};
#endif
