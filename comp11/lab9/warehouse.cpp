#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
//
// implementation of an Warehouse class
//

#include "warehouse.h"

//
// A constructor that initializes all quantities to zero
//
Warehouse::Warehouse()
{
    for(int i=0; i<NUM_PRODUCTS; i++)
    {
	counts[i]=0;
    }
}

//
// A constructor that initializes all quantities to the specified amt
//
Warehouse::Warehouse(int init_qty)
{
    for(int i=0; i<NUM_PRODUCTS; i++)
    {
	counts[i]=init_qty;
    } 
}

// Two restock methods, one for all products
void Warehouse::restock(int additional)
{
    for(int i=0; i<NUM_PRODUCTS; i++)
    {
	counts[i]=additional+counts[i];
    }
}
// A restock for a particular product
void Warehouse::restock(int product, int additional)
{
    counts[product]=additional+counts[product];
}

// Check if a particular product is in stock
bool Warehouse::is_instock(int product)
{
    bool a=false;
    if(counts[product]!=0)
    {
	a=true;
    }
    return a;
}

// ask how many are on hand
int Warehouse::on_hand(int product)
{
    return(counts[product]);
}

//
// sell some amt of some product, return a bool if enough for sale
//
bool Warehouse::remove(int product, int amt)
{
    
    bool a=true;
if((product>9)||(product<0))
    {
	a=false;
    }
    if(counts[product]<amt)
    {
	a=false;
	
    }
    else if(counts[product]>=amt)
    {
	counts[product]=(counts[product]-amt);
    }
    return a;
}

//
// returns the maximum valid product id
//
int Warehouse::maxid()
{
	return NUM_PRODUCTS-1;
}
//
// Which products need to be restocked?
// Pass in a restock level,
// the function fills in a bool array where
// true in position 0 => product 0 is below that level
// true in position 1 => product 1 is below that level
// ...
// return value is number of products that need restock
int Warehouse::need_restock(int minimum, bool isLow[])
{
    int counter=0;
    for(int i=0; i<NUM_PRODUCTS; i++)
    {
	if(counts[i]<minimum)
	{
	    isLow[i]=1;
	    counter++;
	}
	else
	    isLow[i]=0;
    }
    return counter;
}

//
// used internally - determine if the arg is a valid product id
//
bool valid_id(int product)
{
   bool a=false;
   if((product>=0)&&(product<=NUM_PRODUCTS))
       {
         a=true;
       }
      return a;
}

