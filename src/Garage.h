//
// Created by dnc on 04-04-2018.
//

#ifndef CAL_T4GA4_GARAGE_H
#define CAL_T4GA4_GARAGE_H

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

#endif //CAL_T4GA4_GARAGE_H
