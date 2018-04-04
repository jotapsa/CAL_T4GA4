
#ifndef _VEHICLE_H
#define _VEHICLE_H


#include "Aux.h"

class Vehicle {
private:
  garbageType type;
  double capacity;
  double filled;
public:
  Vehicle(garbageType type, double capacity);
  garbageType getType();
  double getCapacity();
  double getFreeSpace();
};


#endif //_VEHICLE_H
