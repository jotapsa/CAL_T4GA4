#include "Vehicle.h"

Vehicle::Vehicle(garbageType type, double capacity) {
  this->type = type;
  this->capacity = capacity;
}

garbageType Vehicle::getType() {
  return this->type;
}

double Vehicle::getCapacity() {
  return this->capacity;
}

double Vehicle::getFreeSpace() {
  return this->capacity-this->filled;
}
