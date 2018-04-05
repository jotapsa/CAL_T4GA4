#include "Station.h"

Station::Station(Node *node, GarbageType type, double capacity) : Building(node) {
  this->capacity = capacity;
  this->garbage = garbage;
}

double Station::getCapacity() {
  return this->capacity;
}

GarbageType Station::getGarbageType() {
  return this->garbage;
}
