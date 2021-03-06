#include "TrigVector.h"

//TrigVector
//Purpose:  Initializes values of class
//Returns:  Nothing
//Bugs   :  None Known
TrigVector::TrigVector()
{
    trigSize=100;
    trigList=new TrigInfo[trigSize];
    numberTrigs=0;
    for(int i=0; i<trigSize; i++)
    {
	trigList[i].Trig="No File";
	trigList[i].counter=0;
	trigList[i].frequency=-1;
    }
    fName="No File";
    language="No File";
    text="";
}

//processDocs
//Purpose:   Runs all TrigVector functions associated with processing documents
//Returns:   Nothing
//Bugs   :   None Known
void TrigVector::processDocs()
{
	text=readFile();
	numberTrigs=Trigrammer();
	frequelizer();
}

//readFile()
//Purpose:   Creates ifstream to read in file, cleans file
//Returns:   String that is cleaned document (may have multiple 
//           consecutive spaces
//Bugs:      Doesn't read in last word sometimes 
//           (french1.txt)||("this that this")
string TrigVector::readFile()
{
    int SIZE=100;
    int stringCount=0;//# strings in document
    string* words;    //array to store them
    words=new string[SIZE];
    string s;        
   
    ifstream fin;
    fin.open(fName.c_str());

    while(!fin.eof())
    {
	fin >> s;
	
	if(!fin.eof())
	{
	    if(stringCount>=SIZE) //if the string array is full, expand it
	    {
	     
		string* temp;
		temp=new string[SIZE*2];
		for(int i=0; i<SIZE*2; i++)
		{
		    if(i<stringCount)
		    temp[i]=words[i];
		    else
			temp[i]="No File";
		}
		delete[] words;
		words=temp;
		temp=NULL;
		SIZE*=2;
	    }

	    int sLength=s.length();	//get length for char loop iterator
	    string edit="";		//empty string to store edits
	    
	    for(int i=0; i<sLength; i++)//tests for letters/#/punc.
	    {
	      
		char c=s[i];
		if(isalpha(c))//ABCs are lower-cased/stored in the edit string
		{
		    c=tolower(c);	       
		    edit+=c;
		}
	       	else if(ispunct(c))//punctuation made spaces, kept in 
		{						   
		    edit+=" ";		       
		}
		else if(isdigit(c))//#s are just deleted, 
		{
 		    string::iterator it;
	    	    it=s.begin()+i;
	    	    s.erase(it);
	    	    sLength-=1;    //adjust for new string length
		}
		    
	    } 
	    words[stringCount]=edit;//store each edited string over origional
	    stringCount++;
	}
       
    }

    for(int i=0; i<stringCount; i++)  //puts all those strings into one big one
    {
	int sLength=words[i].length();//tests if last character is space
	char c=words[i][sLength];     //to add one or not
       				   	    
	if(isspace(c))				       
	{						
	    text=(text + words[i]);
	}
	else     //if the last char in the string is not a space already
                 //it adds a space between strings
	{
	    text=(text + words[i] + " ");
	}
    }  
    text=cleanUp();//call cleanUp to clean spaces
   
    return text;
}

//cleanUp
//Purpose:   Cleans consecutive spaces from text
//Returns:   Ready-to-trigram string
//Bugs   :   None Known
string TrigVector::cleanUp()
{
    bool isClean=false;
    int sLength=text.length();     
    		            
    for(int i=0; i<(sLength-1); i++)		//for every 2-char string
    {
	while(isClean==false)
	{
	    isClean=true;
	    string e="ab";
	    e[0]=text[i];
	    e[1]=text[i+1];

	    if(e=="  ")				//if a double space
	    {					//deletes one
	        string::iterator it;	      
	        it=text.begin()+i;
	        text.erase(it);
	        sLength-=1;		    	//adjust string length
		isClean=false;			//check again
	    }
	}
    }
	   
    return text;
}
	 
//Trigrammer
//Purpose:   Takes text and creates/stores trigrams/counters  
//Returns:   Number of unique trigrams in particular document
//Bugs   :   None known
int TrigVector::Trigrammer()
{
  
    int sLength=text.length();
    int trigCount=0;
    
    for(int i=0; i<((sLength-3)); i++)//to the last trigram in the doc
    {
				     //forms all possible trigrams
	char a=text[i];		       
	char b=text[i+1];
	char c=text[i+2];
	string triGram="";
	triGram+=a;
	triGram+=b;
	triGram+=c;
       
	if(i==0)		    //the first trigram is stored in on its own
	{       
	trigList[0].Trig=triGram;	
	trigCount++;       
	}		
       
	int j = 0; 
	bool isKnown = false;

	while(j<trigSize)		//for every trigram after the first...
	{
	    
	   
	    if(triGram==trigList[j].Trig)	//tests if is known trigram
	    {
	    
		trigList[j].counter+=1;//iterates trigram's counter 
		isKnown=true;
		break;	    	       //goes to make next trigram
	    } 
	    j++;	   
	}

	                               //going to be a new trigram
	if(trigCount>=(trigSize-1))    //expands array of trigrams if necessary
	{
	    TrigInfo* temp;
	    temp=new TrigInfo[trigSize*2];
	    int k=0;
	    while(k<trigSize*2)
	    {
		if(k<trigCount)	      //copies info
		{
 
      	            temp[k].Trig=trigList[k].Trig;
		    temp[k].counter=trigList[k].counter;
		    temp[k].frequency=trigList[k].frequency;
		}
		else		     //standardizes empty indecies
		{			 
		    temp[k].Trig="No File"; 
		    temp[k].counter=0;
		    temp[k].frequency=-1;
		}
		k++;
	    }
		delete[] trigList;
		trigList=temp;
		temp=NULL;
		trigSize*=2;
	}

	if(isKnown==false)		//stores new trigram
	{
	    trigList[trigCount].Trig=triGram;
	    trigList[trigCount].counter+=1;
	    trigCount++;    
	}   
    }    

    return trigCount;	 		   	    
}


//frequelizer
//Purpose:   Calculate individual frequencies of all trigrams within trigLists
//Returns:   Nothing
//Bugs   :   None Known

void TrigVector::frequelizer()
{
    
    double total=0;
    for(int i=0; i<numberTrigs; i++)//calculates the total # trigrams in doc
    {				    //(compounds counters)
	total+=trigList[i].counter;
    }
    for(int j=0; j<numberTrigs; j++)//calculates/stores frequency for trigrams
    {
	trigList[j].frequency=((trigList[j].counter)/(total));   
    }  
}
