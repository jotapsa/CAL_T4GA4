#include "Garage.h"

Garage::Garage(Node &node, std::vector<Vehicle> &vehicles) : Building(node) {

  this->trucks = vehicles;
}

int Garage::getNumberOfTrucks() {
  return this->trucks.size();
}

int Garage::getNumberOfVehiclesOfType(garbageType type) {

  int num = 0;

  for(auto truck: trucks) {
    if(truck.getType() == type) {
      num++;
    }
  }

  return num;
}

int Garage::getNumberOfEmptyTrucks() {

  int num = 0;

  for(auto truck: trucks) {
    if(truck.getFreeSpace() == truck.getCapacity()) {
      num++;
    }
  }

  return num;
}
