Jake Austin
Comp15 Project 1
ReadMe

This program has 4 header files and 4 cpp files in addition to main.

customer.h	 --All associated customer info/functions
customer.cpp     --included within nodes and queues

node.h           --node that holds pointer to a customer and to next node
node.cpp         --included within queues

queue.h          --linked list and associated functions (add/remove...)
queue.cpp        --included within supermarket

supermarket.h    --functions to load/store customers and run simulations
supermarket.cpp

main.cpp

It is compiled as: 
g++ -Wall -Wextra node.cpp customer.cpp queue.cpp supermarket.cpp main.cpp
------
Known Bugs:
in supermarket.cpp
   -warning, results from getShortest function, causes no problems



I need to write a makefile/compile script
I need to write a findings entry
I need to learn how the fuck to use the runall script