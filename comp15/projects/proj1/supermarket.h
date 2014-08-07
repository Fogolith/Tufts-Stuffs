#include "customer.h"
#include "queue.h"
/*

Class Supermarket

-takes in customer file
-run simulation
	-four seperate simulation functions, Queues declared in function

*/
class Supermarket
{

public:
//default constructor
    Supermarket();

//load customer information, stores into Queue pool
    void load(string fname);

//returns queue with fewest customers when passed queues
    Queue* getShortest(Queue* a, Queue* b, Queue* c, Queue* d);

//run the program, increment time and take customers from pool in sequence
//single queue single register
    void run_sim();
//4 queues 4 registers
    void run_sim2();
//2 express queue, 2 regular queue
    void run_sim3();
//1 queue with 4 registers
    void run_sim4();

//Queue to hold customer prior to individual arrival times, accessed by all sims
    Queue* pool;

//void mergeSort (for lab4)
    Queue* mergeSort(Queue* toBeSorted);
    Queue* combine(Queue* one, Queue* two);
    void print(Queue* getPrint);
private:
//taken at load in
    int numCustomers;
//incremented with the Queue::checkOut function
    int numCheckedOut;
//time
    int time;
};
