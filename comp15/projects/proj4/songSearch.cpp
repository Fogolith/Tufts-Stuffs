//Jake Austin
//Comp15
//SongSearch
#include "songSearch.h"

songSearch::songSearch()
{
    for(int i=0; i<hashSize; i++)
    {
	hashTable[i]=new wordNode;
    }
}

void songSearch::loadSongs()
{
    ifstream fin;
    fin.open(fName.c_str());

    int song_count = 0;

  // -- While more data to read...
    while ( ! fin.eof() ) 
    {

    // -- First line is the artist
        string artist;
        getline(fin, artist);

        if (fin.fail()) break;

    // -- Second line is the title
        string title;
        getline(fin, title);

        if (fin.fail()) break;

        song_count++;
        if (song_count % 10000 == 0) 
        {
	    cout << "At " << song_count << " Artist: " << artist;
            cout << " Title: " << title << endl;
        }

        song* newSong=new song;
        newSong->setArtist(artist);
        newSong->setTitle(title);

    // -- Then read all words until we hit the special <BREAK> token
    bool done = false;
    string word;
    while ( ! done)
    {
      fin >> word;
      if (word == "<BREAK>") 
      {
	done = true;
      } 
      else 
      {
	  word=cleanUp(word);//take out capitals/punctuation
	  bool isNew=true;
	  newSong->addLyric(word);
//word is added to lyric, then checked if it is unique to the song
	  for(unsigned int i=0; i<newSong->words.size(); i++)
	  {
	      if(word==newSong->words[i]->word)
	      {
		  isNew=false;
		  newSong->words[i]->num+=1;//increase # of occurances
		  //add occurance to list of this word for this song
	    newSong->words[i]->indecies.push_back((newSong->getNumLyrics()-1));
	      }
	  }
	  if(isNew)//is new in THIS song
	  {
	      uniqueWord* newWord=new uniqueWord;
	      newWord->word=word;
	      newWord->num=1;
	      newWord->indecies.push_back((newSong->getNumLyrics()-1));
	      newSong->words.push_back(newWord);
	  }
       }
    }
        addSong(newSong);//add song to song database
        linkSong(newSong);//link song to ALL unique words in song
        fin.ignore(); 
    }
}

void songSearch::linkSong(song* linking)
{ 
//for all unique words in the linking song
    for(unsigned int i=0; i<linking->words.size(); i++)
    {
	string a=linking->words[i]->word;   
        uint32_t hashcode = hash_string(a);
        int index = hashcode % hashSize;
//hashes word, checks if it is already in hash table
        if(hashTable[index]->isEmpty)
        {
	    wordNode* addHash=new wordNode;
	    addHash->theWord=new word;
	    addHash->theWord->setWord(a);
            addHash->theWord->addToTop(linking);
            hashTable[index]=addHash;
	    hashTable[index]->isEmpty=false;
        }
        else//hashes to occupied address
        {
            bool isUnique=true;
            wordNode* temp=hashTable[index];
	    int counter=0;
	    while(temp!=NULL)
	    {
//is a word already in the hash table, links song to that word
		if(temp->theWord->getWord()==a)
		{
		    temp->theWord->addToTop(linking);
		    isUnique=false;
		    break;
		}
//new word, adds new word to linked list at that hash index
		else if(temp->next==NULL)
		{
		    wordNode* addHash=new wordNode;
		    addHash->theWord=new word;
		    addHash->theWord->setWord(a);
		    temp->next=addHash;
		    addHash->theWord->addToTop(linking);
		    break;
		}
		temp=temp->next;
		counter++;
	    }
        }
    }
}
string songSearch::cleanUp(string a)
{
    int sLength=a.length();
    string edit="";
    for(int i=0; i<sLength; i++)//tests for letters/#/punc.
    {	      
        char c=a[i];
	if(isalpha(c))//ABCs are lower-cased/stored in the edit string
	{
	    c=tolower(c);	       
	    edit+=c;
	}
		    
    }
    return edit;
} 
void songSearch::addSong(song* adding)
{
    database.push_back(adding);
}

void songSearch::setfName(string a)
{
    fName=a;
}

void songSearch::wordSearch(string a)
{
    string search=cleanUp(a);
    uint32_t hashcode = hash_string(search);
    int index = hashcode % hashSize;

    if(hashTable[index]->isEmpty)
    {
	cout << "No song has that word" << endl;
    }
    else
    {
	bool found=false;
	wordNode* temp=hashTable[index];
	while(temp!=NULL)
	{
	    if(temp->theWord->getWord()==search)
	    {
		temp->theWord->printSongs();
		found=true;
	    }
	    temp=temp->next;
	}
	if(found==false)
	{
	    cout << "No song has that word" << endl;
	}
    }
}


