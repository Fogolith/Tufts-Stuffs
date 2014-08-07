#include "BST.h"

int main(int agrc, char* argv[])
{
    if(agrc!=2)
    {
	cout << "invalid command line argument, enter";
	cout << " './a.out' and one filename" << endl;
	return 0;
    }
    string fname=argv[1];
    vector<Animal> animals;

    ifstream fin;
    fin.open(fname.c_str());

    string name="";
    int numAnimals=0;
    int traits[16];
    while(!fin.eof())
    {
	fin >> name;
	if(!fin.eof())
	{
	    for(int i=0; i<16; i++)
	    {
		fin >> traits[i];
	    }
            Animal* temp=new Animal(name, traits);
	    animals.push_back(*temp);
	    numAnimals++;
	}
    }

    cout << "made it here" << endl;

    BST tree;
    tree.load(animals, numAnimals);
    cout << "loaded" << endl;
    tree.inorderPrint();

/*
for(unsigned int i=0; i<animals.size(); i++)
{
    cout << animals[i].name << endl;
    for(int j=0; j<16; j++)
    {
	cout << animals[i].traits[j] << endl;
    }
}
*/
     return 0;
}
