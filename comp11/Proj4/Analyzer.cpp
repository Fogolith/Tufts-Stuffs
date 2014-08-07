#include "Analyzer.h"

//Analyzer()
//Purpose:   Initializes values for the analyzer class
//Returns:   Nothing
//Bugs:      None Known
Analyzer::Analyzer()
{
    LSIZE=2;
    USIZE=2;   			
    langList=new Language[LSIZE];  //array of languages (all empty to start)
    languageCount=0;
    unknowns=new TrigVector[USIZE];//array of Trigram vectors for the unknown 
                                   //files (also empty)
    unknownCount=0;
}					        

//run
//Purpose:   Calls all program's functions
//Returns:   Nothing
//Bugs   :   None Known
void Analyzer::run()
{
    readIn();
    process();
    printResults();
}

//process
//Purpose:   Calls Language/TrigVector processing functions
//Returns:   Nothing
//Bugs   :   None Known
void Analyzer::process()
{
    for(int i=0; i<unknownCount; i++)//for all unknown TrigVectors
    {
	unknowns[i].processDocs();	
    }

    for(int i=0; i<languageCount; i++)//for all languages...
    {
	for(int j=0; j<langList[i].vectorCount; j++)//all of their TrigVectors
	{
	    langList[i].docs[j].processDocs();			    
	}
	langList[i].processLang();//process languages after TrigVectors
    }
}

//readIn()
//Purpose:   Reads in master file, stores language/filename for all TGV read in
//	     Organizes all TGVs into LANGUAGEs and unknown TGVs
//Returns:   Nothing
//Bugs:      None Known
void Analyzer::readIn()
{
    int LSIZE=2;      //do these need to be double declared (see above)
    int USIZE=2;
    int UnknownCounter=0;//also double declared but
    int LangCounter=1;	 //assigned to class variables at end of function
    string s=" ";

    cin >> s; //first line of masterFile read on own (can't know if it will be
  	      //unknown or known)

    if(s=="Unknown")	    
    {			       
	for(int i=0; i<USIZE; i++)
        {
            if(unknowns[i].language=="No File")//sets language and filename for
                                               // unused, UNKNOWN vector
	    {
	        unknowns[i].language=s;
	        cin >> s;
	        unknowns[i].fName=s;
		UnknownCounter++;
	    }
        }	
    }   

    else 						//creates new language
    {
	    langList[0].language=s;			//class language
    	    langList[0].docs[0].language=langList[0].language;	//Doc language
    	    cin >> s;
	    langList[0].docs[0].fName=s;			//Doc fName
            langList[0].vectorCount++;
	   
    }

    while(s!="END")					//using cin/END
    {
	cin >> s;
     	if(s=="END")
	{
	    break;
	}
	if(LangCounter>=LSIZE)		 //expands array of languages if needed
	{
	    Language* temp;
	    temp=new Language[LSIZE*2];
	    for(int i=0; i<LangCounter; i++)
	    {
		temp[i].vectSize=langList[i].vectSize;	//copies all LANG info
		temp[i].vectorCount=langList[i].vectorCount;

		temp[i].language=langList[i].language;
		for(int j=0; j<langList[i].vectorCount; j++)//goes through all
                                                            // stored TGVs
		{
		    temp[i].docs[j].language=langList[i].docs[j].language;
                                                            //copes TGV info
		    temp[i].docs[j].fName=langList[i].docs[j].fName;
		}	         
	    }
	    delete[] langList;
	    langList=temp;
	    temp=NULL;
	    LSIZE*=2;	
	}

	if(UnknownCounter>=USIZE) //expands array for unknown vectors if needed
	{
	    TrigVector* temp;
	    temp=new TrigVector[USIZE*2];
	    for(int i=0; i<UnknownCounter; i++) //copes all TGV info
	    {
		temp[i].fName=unknowns[i].fName;
		temp[i].language=unknowns[i].language;
	    }
	    delete[] unknowns;
	    unknowns=temp;
	    temp=NULL;
	    USIZE*=2;
	  
	}

	if(s=="Unknown")    //stores TGV filename and language in unknown array
	{
	    for(int i=0; i<USIZE; i++)
	    {
		if(unknowns[i].language=="No File")
		{
		    unknowns[i].language=s;
		    cin >> s;
		    unknowns[i].fName=s;
		    UnknownCounter++;
		    break;
		}
	    }
	     
	      
	}
        else				//not END||Unknown
	{
	    bool knownLang=false;
	      for(int i=0; i<LangCounter; i++)//checks if known language type
	      {
		  if(s==langList[i].language)//if it is...
	          {
		      knownLang=true;

		        if(langList[i].vectorCount>=langList[i].vectSize)
                        //checks room in language's TGV array, expands
		        {
			    TrigVector* temp;
			    temp=new TrigVector[langList[i].vectSize*2];
			    for(int j=0; j<langList[i].vectSize*2; j++)
			    {
				if(j<langList[i].vectorCount)	
                                //copes necessary TGV info
				{
				temp[j].language=langList[i].docs[j].language;
				temp[j].fName=langList[i].docs[j].fName;
				}	
			    }
			    delete[] langList;
			    langList[i].docs=temp;
			    temp=NULL;
			    langList[i].vectSize*=2;
			}

                        //when there is room
			for(int j=0; j<langList[i].vectSize; j++) 
		        {			        
		            if(langList[i].docs[j].language=="No File")   
                            //stores filename/language in unused TGV
		            {
			        langList[i].docs[j].language=s;
			        cin >> s;
				langList[i].docs[j].fName=s;
			        langList[i].vectorCount++;		
			        break;
		            } 
		        }
		    }
	      }
		    
	      if(knownLang==false)//not "Unknown", or known but NEW language
	      {
	          for(int i=0; i<LSIZE; i++)
	          {
	              if(langList[i].language=="No File")
                      //stores info in unused language class
		      {
		          langList[i].language=s;
		          langList[i].docs[0].language=s;
		          cin >> s;
		          langList[i].docs[0].fName=s;
		          LangCounter++;
		          langList[i].vectorCount++;
   
		          break;
		      }
	         }
	     }
      }
    }
    languageCount=LangCounter;
    unknownCount=UnknownCounter;
}

 
//compare
//Purpose:   Compares TrigInfo arrays of an unknown document vs. a Language
//Returns:   Double, quotient of the comparing equation
//Bugs   :   None Known
double Analyzer::compare(Language a, TrigVector b)
{
   
    double numerator=0;//=(totalC)
    double denominator=0;//=(totalA*totalB)
    double totalA=0;
    double totalB=0;
    double nums[a.numberTrigs];//for freqA*freqB of like trigrams in TGV/LANG
    int numCount=0;//number of corresponding trigrams

    for(int i=0; i<b.numberTrigs; i++)
    {
	totalA+=((b.trigList[i].frequency)*(b.trigList[i].frequency));
    }
    totalA=sqrt(totalA);
    //totalA == sqrt(sum(unknown trigram frequencies^2))
    for(int i=0; i<a.numberTrigs; i++)
    {
	totalB+=((a.aggregate[i].frequency)*(a.aggregate[i].frequency));
    }
    totalB=sqrt(totalB);
    //totalB == sqrt(sum(language trigram frequencies^2))

    for(int i=0; i<a.numberTrigs; i++)
    {
	for(int j=0; j<b.numberTrigs; j++)
	{
	    if(a.aggregate[i].Trig==b.trigList[j].Trig)//if same trigram found
	    {
	 nums[numCount]=((a.aggregate[i].frequency)*(b.trigList[j].frequency));
	 numCount++;//nums gets Ai*Bi, numCount increased 1
		break;
	    }
	}
    }
    
    double totalC=0;
    for(int i=0; i<numCount; i++)//summation of multiplied frequencies
    {	
	totalC+=nums[i];
    }

    numerator=totalC;
    denominator=(totalA*totalB);
    
    return (numerator/denominator);
}

//printResults
//Purpose:   Calls compare for each unknown/Lang combination, prints results
//Returns:   Nothing
//Bugs   :   None Known
void Analyzer::printResults()
{
    
    double a;
    for(int i=0; i<unknownCount; i++) // for all unknowns
    {
	cout << unknowns[i].fName << endl;

	for(int j=0; j<languageCount; j++)//for all languages
	{
	    a=compare(langList[j], unknowns[i]);//compare
	    int b=(a*100);                      //change to % 
	    cout << setw(10) << langList[j].language << setw(15) << b << endl;
	}
	cout << endl;
    }
    
}
