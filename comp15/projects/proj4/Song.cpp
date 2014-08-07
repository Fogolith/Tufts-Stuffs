//Jake Austin
//Comp15
//SongSearch
#include "Song.h"

void song::setArtist(string a)
{
    artist=a;
}

string song::getArtist()
{
    return artist;
}

void song::setTitle(string a)
{
    title=a;
}

string song::getTitle()
{
    return title;
}

void song::addLyric(string a)
{
    lyrics.push_back(a);
}

string song::getLyric(int a)
{
    return lyrics[a];
}

int song::getNumLyrics()
{
    return lyrics.size();
}

void song::printWord(string print)
{
    for(unsigned int i=0; i<words.size(); i++)
    {
	if(words[i]->word==print)//find the word
	{
	    for(unsigned int j=0; j<words[i]->indecies.size(); j++)
	    {
		printLyrics(words[i]->indecies[j]);
	    }//print every occurance of that word in the lyrics
	}
    }
}

void song::printLyrics(int index)
{
    cout << "Title: " << title << endl;
    cout << "Artist " << artist << endl;
    cout << "Context: ";

    int fromStart=index;//to avoid segfaulting off lyrics vector
    int fromEnd=(getNumLyrics()-index);
    if((fromStart>2)&&(fromEnd>2))
    {
	cout << getLyric(index-2) << " " << getLyric(index-1) << " ";
	cout << getLyric(index) << " " << getLyric(index+1) << " ";
	cout << getLyric(index+2);
    }
    else if(fromStart<=2)
    {
	cout << getLyric(0) << " " << getLyric(1) << " " << getLyric(2);
	cout << " " << getLyric(3) << " " << getLyric(4);
    }
    else if(fromEnd<=2)
    {
	cout << getLyric(index-4) << " " << getLyric(index-3) << " ";
	cout << getLyric(index-2) << " " << getLyric(index-1) << " ";
	cout << getLyric(index);
    }
    
    cout << endl << endl;
}
