//Jake Austin
//Comp15
//SongSearch
#include "Word.h"

//A wordNode goes in the hashTable
struct wordNode
{
    bool isEmpty;
    word* theWord;
    wordNode* next;
    wordNode()
    {
	isEmpty=true;
	theWord=NULL;
        next=NULL;
    }
};

const int hashSize=60000;

class songSearch
{
private:
   
    string fName;
    vector<song*> database;
    wordNode* hashTable[hashSize];
public:
    songSearch();
//reads in file, creates SONGS with associated info, calls LINK to set hash
    void loadSongs();
    void wordSearch(string a);
    void setfName(string a);
    void addSong(song* adding);
//called on each song, linkSong reads through all unique words in the song,
//hashes them and either creates new words and links song to them or links
//song to existing word
    void linkSong(song* linking);
    string cleanUp(string a);
}; 




