#ifndef TrigInfoSTR
#define TrigInfoSTR

#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<cmath>

using namespace std;
using std::string;

//This header file is just for this struct, which will be the data type for all TrigInfo arrays

struct TrigInfo
{
    string Trig;		//for trigram
    int counter;		//for  number of occurances
    double frequency;		//for frequency within a group of trigrams/counters
};
#endif
