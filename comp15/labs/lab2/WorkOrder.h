// 
// WorkOrder.h
// Created by Aaron Tietz February 5, 2012
//

#ifndef AARON_ORDER_H
#define AARON_ORDER_H

#include <string>

class WorkOrder{
public:
  WorkOrder(std::string name, double priorityLevel);
    // Postconditions: this->name and this->priorityLevel are
    //	set to given values
    
  std::string Name() const;
    // Postcondition: value of name is returned
    
  double PriorityLevel() const;
    // Postcondition: value of priorityLevel is returned
    
private:
  std::string name;
  double priorityLevel;
};

#endif

