#include "Language.h"


//Language()
//Purpose:   Initializes values for class
//Returns:   Nothing
//Bugs:      None known
Language::Language()
{
    vectSize=10;
    trigSize=100;
    docs=new TrigVector[vectSize];		   
    aggregate=new TrigInfo[trigSize];
    for(int i=0; i<trigSize; i++)
    {
	aggregate[i].Trig="No File";
	aggregate[i].counter=0;
	aggregate[i].frequency=0;
    }
    numberTrigs=0;
    language="No File";
    vectorCount=0;
}

//processLang
//Purpose:   Runs all language-level functions
//Returns:   Nothing
//Bugs   :   None Known
void Language::processLang()
{
    numberTrigs=consolidate();
    Lfrequelizer();
}

//consolidate()
//Purpose:   Aggregates trigram info for all documents of same type language
//Returns:   Number of unique trigrams in LANGUAGE
//Bugs:      None Known
int Language::consolidate()
{
   
    aggregate[0].Trig=docs[0].trigList[0].Trig;//stores first LANG trigram
                                               //NOT counter (will copy when
                                               // it comes up as known)
    int stored=1;
    
    for(int i=0; i<vectorCount; i++)//for all the documents in this language
    {
      
	for(int j=0; j<docs[i].numberTrigs; j++)//for all trigrams of doc
	{
	    bool isKnown=false;     
	   
	    for(int k=0; k<stored; k++)//for how many have already been stored
	    {
		if(docs[i].trigList[j].Trig==aggregate[k].Trig)//if it's known
		{
		  
		    aggregate[k].counter+=docs[i].trigList[j].counter;
                    //add TGV trigram counter to aggregate trigram counter
		    isKnown=true;	 
		    break;
		}	   
	    }	    

            //new LANG trigram coming	
    	    if(stored>=trigSize)//language's aggregate array needs to expand
            {
                TrigInfo* temp;
                temp=new TrigInfo[trigSize*2];
	        int a=0;
	        while(a<trigSize*2)
	        {
	            if(a<stored)	  //stores known trigrams/counters
	            {
	                temp[a].Trig=aggregate[a].Trig;
		        temp[a].counter=aggregate[a].counter;
	            }
	            else if(a<trigSize*2) //sets unused indecies 
	            {
		        temp[a].Trig="No File";
		        temp[a].counter=0;
		        temp[a].frequency=0;
	            }
		    a++;
	        }    
  
	        delete [] aggregate;
	        aggregate=temp;
	        temp=NULL;
	        trigSize*=2;
            }
	          //stores as new LANG trigram, takes counter from doc.trigList
	    if(isKnown==false)
	    {
		
    	        aggregate[stored].Trig=docs[i].trigList[j].Trig;
                aggregate[stored].counter=docs[i].trigList[j].counter;
                stored++;   
	    }
	}
    }
    return stored;
}

//frequelizer
//Purpose:   Calculate/store frequencies of individual trigrams in aggregate
//Returns:   Nothing
//Bugs:      None Known
void Language::Lfrequelizer()
{
    double total=0;
    for(int j=0; j<numberTrigs; j++)//calculates total trigram for language
    {
	total+=aggregate[j].counter;
      
    }
    for(int j=0; j<numberTrigs; j++)//calculates frequencies based on total
    {
	aggregate[j].frequency=((aggregate[j].counter)/(total));
    
    }
  
}
