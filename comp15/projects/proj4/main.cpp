#include "songSearch.h"
#include <time.h>

double get_current_time();
int main(int agrc, char* argv[])
{
    if(agrc!=2)
    {
       cout << "Invalid command line- enter './songSearch' 'filename'" << endl;
    }
    songSearch mySearch;
    mySearch.setfName(argv[1]);

    double start=get_current_time();
    mySearch.loadSongs();
    double end=get_current_time();
    cout << "Load Time: " << (end-start) << endl;

    string searchTerm;
    while(searchTerm!="quit")
    {
	cout << "Enter search term (type 'quit' to exit): ";
	cin >> searchTerm;
        double start=get_current_time();
	mySearch.wordSearch(searchTerm);
	double end=get_current_time();
	cout << "Search Time: " << (end-start) << endl;
    }
    return 0;
}

double get_current_time()
{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    double res=((double)ts.tv_sec + ((double)ts.tv_nsec)/1000000000.0);
    return res;
}

