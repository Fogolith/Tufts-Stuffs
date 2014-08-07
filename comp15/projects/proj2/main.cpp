#include "generator.h"
/*

assumes "Sentence" is the highest level grammar rule
assumes "strings" will never be entered as a (non)terminal
generates a sentance for every word entered by user ("How are you" generates 3 sentences)


*/
int main(int agrc, char* argv[])
{
    if(agrc!=2)
    {
	cout << "Invalid command line argument, enter";
	cout <<" './chat' and one filename" << endl;
	return 0;
    }
    string fname=argv[1];
    generator chat;
    srandom(time(NULL));

    chat.load(fname);

    string entry;
    string response;

    cout << "Type 'Hi' for a response or 'quit' to exit" << endl;
    cin >> entry;

    while(entry!="quit")
    {
	response=chat.gen(chat.sentence);
	cout << response << endl << endl;
	cout << "waiting for response..." << endl;
	cin >> entry;
    }


      
//Big loop to print productions, associated rules, and associated terminals
/*
    for(unsigned int j=0; j<chat.grammar.size(); j++)
    {
	cout << chat.grammar[j].NT << endl;
     
	
	    for(unsigned int k=0; k<chat.grammar[j].rules.size(); k++)
	    {
                for(unsigned int i=0; i<chat.grammar[j].rules[k].pieces.size(); i++)
                {
	            cout << chat.grammar[j].rules[k].pieces[i] << " ";
                }
	        cout << endl;
	    }
	
	if(chat.grammar[j].hasLeaves)
	{
	    for(unsigned int i=0; i<chat.grammar[j].words.size(); i++)
	    {
		cout << chat.grammar[j].words[i] << " ";
	    }
	    cout << endl;
	}
	cout << endl;
    }
*/
    return 0;
}
