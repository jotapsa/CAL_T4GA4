//
// Created by dnc on 04-04-2018.
//

#ifndef CAL_T4GA4_STATION_H
#define CAL_T4GA4_STATION_H


#include "Building.h"
#include "Aux.h"

class Station:Building {
  garbageType garbage;
  double capacity;
public:
  Station(Node &node, double capacity, garbageType garbage);
  garbageType getGarbageType();
  double getCapacity();
};


#endif //CAL_T4GA4_STATION_H
