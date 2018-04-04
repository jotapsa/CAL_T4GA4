#ifndef _GARAGE_H
#define _GARAGE_H

#include "Building.h"
#include "Vehicle.h"

class Garage : Building {
  std::vector<Vehicle> trucks;
public:
  Garage(Node &node, std::vector<Vehicle> &vehicles);
  int getNumberOfTrucks();
  int getNumberOfVehiclesOfType(garbageType type);
  int getNumberOfEmptyTrucks();
};

#endif //_GARAGE_H
