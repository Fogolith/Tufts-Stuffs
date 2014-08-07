//Jake Austin
//Comp15
//SongSearch
#include "Song.h"

//songNode for linked list of top10 songs based on numRefs
struct songNode
{
    song* theSong;
    int numRefs;
    songNode* next;
    songNode()
    {
	next=NULL;
    }
};

class word
{
private:
    string thisWord;
    songNode* topTen;

public:
    word();
    void setWord(string a);
    string getWord();
//adds song pointer to topTen in order of numRefs
    void addToTop(song* hasWord);
//calls print on topTen
    void printSongs();
};
