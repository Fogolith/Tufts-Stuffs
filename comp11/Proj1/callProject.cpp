#include<iostream>
#include<iomanip>
using namespace std;

const int max_calls=1000;		    //max calls in any given array	
const int plan1DayStart=480;		    //start of day on plan1 (in minutes)
const int plan1NightStart=1200;		    //start of night on plan1 (in minutes)
const int plan2DayStart=540;		    //start of day on plan2 (in miuntes)
const int plan2NightStart=1080;		    //start of night on plan2 (in minutes)
const double plan1BasePrice=39.99;
const double plan2BasePrice=69.99;

void storeCalls(int hour[], int min[], int hour2[], int min2[]);
void printArray(int hour[], int min[], int hour2[], int min2[], int numCalls);
int countCalls(int hour[], int min[], int hour2[], int min2[]);
void convert2Minutes(int hours[], int mins[], int TimeMin[],  int numCalls);
void DayOrNightPlan1(int beginTimeMin[], int endTimeMin[], int dayCalls[], int nightCalls[], int numCalls);
void DayOrNightPlan2(int beginTimeMin[], int endTimeMin[], int dayCalls2[], int nightCalls2[], int numCalls);
void charge1(int dayCalls[], int nightCalls[], int numCalls, double chargePlan1[]);
void charge2(int dayCalls2[], int numCalls, double chargePlan2[]);
void totalAndCharge1(int dayCalls[], int nightCalls[], double chargePlan1[], int totalDayMin1, int totalNightMin1, double totalCharge1, int numCalls);
void totalAndCharge2(int dayCalls2[], int nightCalls2[], double chargePlan2[], int totalDayMin2, int totalNightMin2, double totalCharge2,int numCalls);
int totalMin(int calls[], int numCalls);
double totalCharge(double charge[], int numCalls);
void printAnswer(int hour[], int min[], int hour2[], int min2[], int dayCalls[], int nightCalls[], int dayCalls2[], int nightCalls2[],int  totalDayMin1, int totalDayMin2, int totalNightMin1, int totalNightMin2, double totalCharge1, double totalCharge2, double chargePlan1[], double chargePlan2[], int numCalls);	


int main()
{
    int hour[max_calls];	     //declaring 4 arrays for beggining hour/minute and end hour/minute
    int min[max_calls];
    int hour2[max_calls];
    int min2[max_calls];
    int beginTimeMin[max_calls];     //array for begin time IN MINUTES
    int endTimeMin[max_calls];	     //array for end time IN MINUTES
    int dayCalls[max_calls];	     //array for daytime minutes used on plan1
    int dayCalls2[max_calls];	     //array for daytime minutes used on plan2
    int nightCalls[max_calls];	     //array for nighttime minutes used on plan1
    int nightCalls2[max_calls];	     //array for nighttime minutes used on plan2
    double chargePlan1[max_calls];   //array for charge per call on plan1
    double chargePlan2[max_calls];   //array for charge per call on plan2
    int numCalls;		     //number of calls in a dataset
    int totalDayMin1=0;		     //ints for total day/night minutes for plans 1&2, doubles for total charge (starting at base price)
    int totalNightMin1=0;
    double totalCharge1=plan1BasePrice;	
    int totalDayMin2=0;
    int totalNightMin2=0;
    double totalCharge2=plan2BasePrice;		
       
//function calls
    storeCalls(hour, min, hour2, min2);
    numCalls=countCalls(hour, min, hour2, min2);
    convert2Minutes(hour, min, beginTimeMin, numCalls);
    convert2Minutes(hour2, min2, endTimeMin, numCalls); 
    DayOrNightPlan1(beginTimeMin, endTimeMin, dayCalls, nightCalls, numCalls);
    DayOrNightPlan2(beginTimeMin, endTimeMin, dayCalls2, nightCalls2, numCalls);
    charge1(dayCalls, nightCalls, numCalls, chargePlan1);
    charge2(dayCalls2, numCalls, chargePlan2);
    totalDayMin1=totalMin(dayCalls, numCalls);
    totalNightMin1=totalMin(nightCalls, numCalls);
    totalDayMin2=totalMin(dayCalls2, numCalls);
    totalNightMin2=totalMin(nightCalls2, numCalls);
    totalCharge1=(totalCharge1 +(totalCharge(chargePlan1, numCalls)));
    totalCharge2=(totalCharge2 +(totalCharge(chargePlan2, numCalls)));
    printAnswer(hour, min, hour2, min2, dayCalls, nightCalls, dayCalls2, nightCalls2, totalDayMin1, totalDayMin2, totalNightMin1, 
		totalNightMin2, totalCharge1, totalCharge2, chargePlan1, chargePlan2, numCalls);
    return 0;
}



//Function Definitions

//StoreCalls
//Purpose    Read in call data and store
//argument   arrays - hour, min, hour2, min2
//returns    -nothing-
//
void storeCalls(int hour[], int min[], int hour2[], int min2[])
{
    
    int i;
    char colon;
    char test;
    int terminate=max_calls;
    while(i<terminate)
    {
	cin >> test;
	if (test=='p')			//checks for p/s, cin line if p
	{
		cin >> hour[i];
		cin >> colon;
		cin >> min[i];
		cin >> hour2[i];
		cin >> colon;
		cin >> min2[i];
		i++;


	}
	else
	{
	    terminate=i;		//if not p, terminates loop
	}
    }
   
}



//countCalls
//purpose    counts the number of calls in a dataset
//argument   arrays hour, min, hour2, min2
//returns    int for number of calls in dataset
//
int countCalls(int hour[], int min[], int hour2[], int min2[])   //basically same function as storeCalls but returns counter
{								 //instead of being a void function
    
    int counter;
    char colon;
    char test;
    int terminate = max_calls;
    while(counter<terminate)
    {
	cin >> test;
	if(test=='p')
	{
		cin >> hour[counter];
		cin >> colon;
		cin >> min[counter];
		cin >> hour2[counter];

		cin >> colon;
		cin >> min2[counter];
		counter++;
	
	}
	else
	{
	    terminate = counter;
	}
    }
    return counter;
}


//convert2Minutes
//Purpose      converts hour:min to total minutes, must be used for begintime + endtime, stores in array
//argument     3 arrays (hour/min and the array the new time will be stored in), numCalls
//returns      -nothing-
//
void convert2Minutes(int hours[], int mins[], int TimeMin[], int numCalls)
{

    for(int i=0; i<numCalls; i++)
    {
	TimeMin[i]=(hours[i]*60)+(mins[i]);
    }

}


//DayOrNightPlan1
//purpose     determines whether a call was made in daytime hours or nighttime hours, stores call duration
//argument    arrays beginTimeMin, endTimeMin - stored in arrays dayCalls/nightCalls, int numCalls
//return      -nothing-
//
void DayOrNightPlan1(int beginTimeMin[],int endTimeMin[], int dayCalls[], int nightCalls[], int numCalls)
{
       for(int i=0; i<numCalls; i++)
    {
	if((beginTimeMin[i]>=plan1DayStart)&&(beginTimeMin[i]<plan1NightStart)) //tests for calls made in daytime hours
	{
	    if((endTimeMin[i]-beginTimeMin[i])<0)				//tests for calls that pass over midnight
	    {
		dayCalls[i]=(1440+(endTimeMin[i]-beginTimeMin[i]));
		nightCalls[i]=0;
	    }
	    else
	    {
	    dayCalls[i]=(endTimeMin[i]-beginTimeMin[i]);			//all other daytime calls
	    nightCalls[i]=0;							//avoid dead squirrels in nighttime calls
	    }
	}
	else 									//tests for nighttime calls
	{
	    if((endTimeMin[i]-beginTimeMin[i])<0)				//test for call that pass over midnight
	    {
		nightCalls[i]=(1440+(endTimeMin[i]-beginTimeMin[i]));
		dayCalls[i]=0;							//avoid dead squirrels
	    }
	    else

	    {
	    nightCalls[i]=(endTimeMin[i]-beginTimeMin[i]);
	    dayCalls[i]=0;
	    }
	}
    }
}


//DayOrNightPlan2
//purpose     determines whether a call was made in daytime or nightime hours, stores call duration FOR PLAN2
//argument    arrays beginTimeMin, endTimeMin - stored in arrays dayCalls2/nightCalls2, int numCalls
//returns     -nothing-
//ALL COMMENTS THE SAME AS DayOrNightPlan1
//
void DayOrNightPlan2(int beginTimeMin[], int endTimeMin[], int dayCalls2[], int nightCalls2[], int numCalls)
{
    for(int i=0; i<numCalls; i++)
    {
	if((beginTimeMin[i]>=plan2DayStart)&&(beginTimeMin[i]<plan2NightStart))
	{
	    if((endTimeMin[i]-beginTimeMin[i])<0)				
	    {
		dayCalls2[i]=(1440+(endTimeMin[i]-beginTimeMin[i]));
		nightCalls2[i]=0;
	    }
	    else
	    {
	    dayCalls2[i]=(endTimeMin[i]-beginTimeMin[i]);
	    nightCalls2[i]=0;
	    }
	}
	else 
	{
	    if((endTimeMin[i]-beginTimeMin[i])<0)
	    {
		nightCalls2[i]=(1440+(endTimeMin[i]-beginTimeMin[i]));
		dayCalls2[i]=0;
	    }
	    else
	    {
	    nightCalls2[i]=(endTimeMin[i]-beginTimeMin[i]);
	    dayCalls2[i]=0;
	    }
	}
    }
}

//Charge1
//purpose       calculates and stores the charge per call on plan1
//argument      arrays dayCalls/nightCalls, numCalls, stores in chargePlan1
//returns       -nothing-
//
void charge1(int dayCalls[], int nightCalls[], int numCalls, double chargePlan1[])
{
    int plan1DayMinutes=450;					
    int plan1NightMinutes=5000;
    int i=0;
    int j=0;
    int a;
    int b;
    int freeDayCalls; 
    int freeNightCalls;

    while((plan1DayMinutes>0)&&(i<numCalls))			//subtracts call durations from free minutes one by one
    {
	plan1DayMinutes=(plan1DayMinutes-dayCalls[i]);

	if(plan1DayMinutes<=0)
	{
	    chargePlan1[i]=(plan1DayMinutes*.45*-1);		//UNTIL minutes run out, negative remainder is charged for minute usage
	}

	freeDayCalls=i+1;					//stores how many calls in the array were free + the first charged call
        i++;
    }

    for(a=freeDayCalls; a<numCalls; a++)			//charges remainder of daytime calls
    {
	chargePlan1[a]=(.45*dayCalls[a]);
    }


    while((plan1NightMinutes>0)&&(j<numCalls))			//All the same stuff for night time minutes
    {
	plan1NightMinutes=plan1NightMinutes-nightCalls[j];
	if(plan1NightMinutes<=0)
	{
	    chargePlan1[i]=(plan1NightMinutes*.45*-1);
	}
	freeNightCalls=j+1;
	j++;
    }

    for(b=freeNightCalls; b<numCalls; b++)
    {
	chargePlan1[b]=(.45*nightCalls[b]);
    }

}

//Charge2
//purpose       calculates and stores the charge per call on plan2
//argument      arrays dayCalls, numCalls, stored in chargePlan2 
//returns       -nothing-
//
void charge2(int dayCalls2[], int numCalls, double chargePlan2[])
{
    int plan2DayMinutes=800;
    int i=0;
    int freeDayCalls;
    while((plan2DayMinutes>0)&&(i<numCalls))				//All the same stuff as plan1 daytime calls, with plan2 rates 
    {
	plan2DayMinutes=plan2DayMinutes-dayCalls2[i];
	if(plan2DayMinutes<=0)
	{
	    chargePlan2[i]=(plan2DayMinutes*.40*-1);			
	}
	i++;
	freeDayCalls=i+1;
    }
   
    for(i=freeDayCalls; i<numCalls; i++)
    {
	chargePlan2[i]=(.40*dayCalls2[i]);
    }									//unlimited nighttime minutes on plan2, don't need to worry about it
    
}


//totalMin
//Purpose    calculates total minutes from call durations
//argument   array (dayCalls/dayCalls2/nightCalls/nightCalls2)
//returns    int
//
int totalMin(int calls[], int numCalls)
{
    int total=0;
    for(int i=0; i<numCalls; i++)
    {
	total=total+calls[i];
    }
    return total;
}

//totalCharge
//purpose       calculates total charge 
//argument      either array chargePlan1/chargePlan2
//returns      double
//
double totalCharge(double charge[], int numCalls)
{
    double total=0;
    for(int i=0; i<numCalls; i++)
    {
	total=total+charge[i];
    }
    return total;
}


//Print Answer
//purpose    	sees out all data in columns
//argument   	arrays hour, min, hour2, min2, dayCalls, nightCalls, dayCalls2, nightCalls2, chargePlan1, chargePlan2, doubles totalCharge1/totalCharge2, and ints numCalls, totalDayMin1, totalDayMin2, totalNightMin1, totalNightMin2  
//returns	-nothing-
//
void printAnswer(int hour[], int min[], int hour2[], int min2[], int dayCalls[], int nightCalls[], int dayCalls2[], int nightCalls2[],int  totalDayMin1, int totalDayMin2, int totalNightMin1, int totalNightMin2, double totalCharge1, double totalCharge2, double chargePlan1[], double chargePlan2[], int numCalls)		
{
    cout << setiosflags(ios::fixed);
    cout << setprecision(2);

    cout << "Begin Time" << setw(15) << "End Time" << setw(15) << "Daytime Min" << setw(15) << "Nighttime Min" << setw(15) << "Charge" << endl;
   

    for(int i=0; i<numCalls; i++)
    {
	cout <<  hour[i] << ":";
	if(min[i]<10)						//conditional prints "01"-"09" instead of "1"-"9" for whatever minute value
	{
	    cout << "0" << min[i];
	}
	else
	{
	    cout << min[i];
	}

	cout << setw(15) << hour2[i] << ":";
	if(min2[i]<10)
	{
	    cout << "0" << min2[i];
	}
	else
	{
	    cout << min2[i];
	}

	cout << setw(15) << dayCalls[i] << setw(15) << nightCalls[i] << setw(15) << chargePlan1[i] << endl;
    }

    cout << endl << "Total Daytime min: " << totalDayMin1 << endl << "Total Nighttime Min: " << totalNightMin1 << endl;
    cout << "Total Monthly Charge: " << totalCharge1 << endl;

    cout << "-------------------------------------------------------------------------------" << endl;

     for(int i=1; i<30; i=i+5)
    {
	cout << setw(0) << endl;
    }

    cout << "Begin Time" << setw(15) << "End Time" << setw(15) << "Daytime Min" << setw(15) << "Nighttime Min" << setw(15) << "Charge" << endl;

    for(int i=0; i<numCalls; i++)
    {
	cout <<  hour[i] << ":";
	if(min[i]<10)
	{
	    cout << "0" << min[i];
	}
	else
	{
	    cout << min[i];
	}

	cout << setw(15) <<  hour2[i] << ":";
	if(min2[i]<10)
	{
	    cout << "0" << min2[i];
	}
	else
	{
	    cout << min2[i];
	}

	cout << setw(15) << dayCalls2[i] << setw(15) << nightCalls2[i] << setw(15) << chargePlan2[i] << endl;
    }
    cout << endl << "Total Daytime min: " << totalDayMin2 << endl << "Total Nighttime Min: " << totalNightMin2 << endl;
    cout << "Total Monthly Charge: " << totalCharge2 << endl;
}
