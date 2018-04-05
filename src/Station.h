#ifndef _STATION_H
#define _STATION_H


#include "Building.h"
#include "Aux.h"

class Station:Building {
  garbageType garbage;
  double capacity;
public:
  Station(Node &node, garbageType type, double capacity);
  garbageType getGarbageType();
  double getCapacity();
};


#endif //_STATION_H
