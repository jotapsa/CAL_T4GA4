#ifndef _STATION_H
#define _STATION_H


#include "Building.h"
#include "Aux.h"

class Station : public Building {
  GarbageType garbage;
  double capacity;
public:
  Station(Node *node, GarbageType type, double capacity);
  GarbageType getGarbageType();
  double getCapacity();
};


#endif //_STATION_H
