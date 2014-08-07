//Jake Austin
//Comp15
//SongSearch
#include "Word.h"

word::word()
{
    topTen=NULL;
}
void word::setWord(string a)
{
    thisWord=a;
}

string word::getWord()
{
    return thisWord;
}

void word::addToTop(song* hasWord)
{
    songNode* temp=topTen;
    songNode* adding=new songNode;  
    adding->theSong=new song;  
    adding->theSong=hasWord;

    int counter=0;
    for(unsigned int i=0; i<hasWord->words.size(); i++)//finds word in song
    {
	string a=hasWord->words[i]->word;
	if(a==thisWord)
	{
	    adding->numRefs=hasWord->words[i]->num;//gets numRefs for word
	    break;
	}
    }
    
    while((counter!=10))//for the top 10 songs by most references
    {
	if(topTen==NULL)//first song linked to this word
	{
	    topTen=new songNode;
	    topTen=adding;
	    break;
	}
	else if(adding->numRefs>temp->numRefs)//is new #1
	{
	    adding->next=temp;
	    topTen=adding;
	    break;
	}
        else if((temp->next==NULL))//added to end
	{
	    temp->next=adding;
	    break;
	}
	else if(adding->numRefs>temp->next->numRefs)//added between songs
	{
	    adding->next=temp->next;
	    temp->next=adding;
	    break;
	}
	
	temp=temp->next;
	counter++;
    }
    
}

void word::printSongs()
{
    songNode* temp=topTen;
    int counter=0;
    while((counter<10)&&(temp!=NULL))
    {
	temp->theSong->printWord(thisWord);
	temp=temp->next;
	counter++;
    }
}
	   
