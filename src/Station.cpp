#include "Station.h"

Station::Station(Node *node, garbageType type, double capacity) : Building(node) {
  this->capacity = capacity;
  this->garbage = garbage;
}

double Station::getCapacity() {
  return this->capacity;
}

garbageType Station::getGarbageType() {
  return this->garbage;
}
