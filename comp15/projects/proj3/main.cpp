//Jake Austin
//Comp15
//Project 3
//4/17/12
#include "Cluster.h"

int main(int agrc, char* argv[])
{
    if(agrc!=4)
    {
	cout << "invalid command line argument, enter";
	cout << " './zoo' ' filename' metric '1/2/3' '# clusters'" << endl;
	return 0;
    }
  
    Cluster zoo;
    zoo.setfName(argv[1]);
    zoo.setMetric(atoi(argv[2]));
    zoo.setStop(atoi(argv[3]));
    unsigned int stop=zoo.getStop();

    zoo.loadAnimals();   
    zoo.mostLegs();   

    while(zoo.allSets.size()!=stop)
    {
    	zoo.mergeClosest();
    }

    zoo.print();

    return 0;
}
