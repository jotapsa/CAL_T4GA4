
#ifndef _VEHICLE_H
#define _VEHICLE_H


#include "Aux.h"

class Vehicle {
private:
  GarbageType type;
  double capacity;
  double filled;
public:
  Vehicle(GarbageType type, double capacity);
  GarbageType getType();
  double getCapacity();
  double getFreeSpace();
};


#endif //_VEHICLE_H
