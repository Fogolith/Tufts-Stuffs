//Jake Austin
//Comp15
//SongSearch
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include "hashfunc.h"
using namespace std;

//a uniqueWord is unique to the song, and has the number of occurances
//as well as a vector of indecies in which it appears in the lyrics
struct uniqueWord
{
    string word;
    int num;
    vector<int> indecies;
};

class song
{
private:

    string artist;
    string title;
    vector<string> lyrics;

public:
   
    vector<uniqueWord*> words;

    void setArtist(string a);
    string getArtist();
    void setTitle(string a);
    string getTitle();

    void addLyric(string a);
    string getLyric(int a);
    int getNumLyrics();
//takes in word, finds indecies that word appears in and calls printLyrics
    void printWord(string print);
//takes in index, prints word and context
    void printLyrics(int index);
};
