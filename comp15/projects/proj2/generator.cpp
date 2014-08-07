#include "generator.h"

generator::generator()
{
}

void generator::load(string fname)
{
    ifstream fin;
    fin.open(fname.c_str());

    string first;
    string second;
    string third;
    while(!fin.eof())
    {
        fin >> first >> second >> third;
	if(!fin.eof())
	{
	    bool isNew=true;
	    for(unsigned int i=0; i<(grammar.size()); i++)//grammar vector 
	    {
		if(first==grammar[i].NT)//non-terminal that has been added
		{
		    isNew=false;
		    if(third==".")//if it is a terminal
		    {
			grammar[i].hasLeaves=true;
			grammar[i].words.push_back(second);
	                rule* temp=new rule;
		        string a="strings";
		        temp->pieces.push_back(a);
		        grammar[i].rules.push_back(*temp);
			//adds it to vector of terminals
			//adds rule to non terminal  
		    }
		    else//new rule, fills vector of pieces and adds rule
		    {
			rule* temp=new rule;
			temp->pieces.push_back(second);
			temp->pieces.push_back(third);
 
			string piece;
			while(piece!=".")//handles all parts of rule
			{
			    fin >> piece;
			    if(piece!=".")
				temp->pieces.push_back(piece);
			}
			grammar[i].rules.push_back(*temp);
		    }
		}
	    }
	   
	    if(isNew)//NT that has not been stored as production yet
	    {
	        production* temp=new production;
	        temp->NT=first;
	    
	        if(third==".")//if it has a terminal
	        {
		    temp->words.push_back(second);
		    temp->hasLeaves=true;
 		    rule* temp1=new rule;
		    string a="strings";
		    temp1->pieces.push_back(a);
		    temp->rules.push_back(*temp1);
	        }
	        else//not a terminal,make a new rule, store in new production
	        {
		    rule* temp1=new rule;
		    temp1->pieces.push_back(second);
		    temp1->pieces.push_back(third);
	            string piece;
	            while(piece!=".")
	            {
	                fin >> piece;
	                if(piece!=".")
	      	            temp1->pieces.push_back(piece);
		    }
		    temp->rules.push_back(*temp1);   
	        }
 		grammar.push_back(*temp);
	    }
        }
    }
//For every terminal added to some non-terminal, the terminal will be added
//to the "words" vector AND a new rule, simply input as "strings,"
//will be added to increase the chance of a word being returned randomly
//---------The probability of a word being returned is proportional to how
//---------many words have been added (Noun Adj Noun will be called 1/2 of
//---------the time if it is the only noun rule and only one terminal 
//---------noun has been added.

    sentence=grammar[0].NT;//sets word for default generate call
}

string generator::gen(string s)
{
    vector<string> terms;//for words returned from recursive calls
    int r=random();

    for(unsigned int i=0; i<grammar.size(); i++)
    {
	if(s==grammar[i].NT)//not a terminal
	{
	    r=r%grammar[i].rules.size();//random number pick a rule
	    for(unsigned int j=0; j<grammar[i].rules[r].pieces.size(); j++)
	    {	
		if(grammar[i].rules[r].pieces.front()!="strings")
		{
		    string a=gen(grammar[i].rules[r].pieces[j]);
		    terms.push_back(a);
		}
		else if(grammar[i].rules[r].pieces.front()=="strings")
		{//returns a random word from the array of terminals
		    int ran=random();
		    ran=ran%grammar[i].words.size();
		    string a=grammar[i].words[ran];
		    terms.push_back(a);
		}
	    }
	}
    }

    string final="";//to be returned
    for(unsigned int i=0; i<terms.size(); i++)//put together returned words
    {
	final+=terms[i];
	final+=" ";			//adds extra spaces depending on #
    }					//of calls

/*
to clean multiple consecutive spaces out of the final sentences,
doesn't totally work

*/
    bool isClean=false;
    int sLength=final.length();     
    		            
    for(int i=0; i<(sLength-1); i++)		//for every 2-char string
    {
	while(isClean==false)
	{
	    isClean=true;
	    string e="ab";
	    e[0]=final[i];
	    e[1]=final[i+1];

	    if(e=="  ")				//if a double space
	    {					//deletes one
	        string::iterator it;	      
	        it=final.begin()+i;
	        final.erase(it);
	        sLength-=1;		    	//adjust string length
		isClean=false;			//check again
	    }
	}
    }
    return final;
}
