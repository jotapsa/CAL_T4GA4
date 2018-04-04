//
// Created by dnc on 04-04-2018.
//

#include "Station.h"

Station::Station(Node &node, double capacity, garbageType garbage) : Building(node) {
  this->capacity = capacity;
  this->garbage = garbage;
}

double Station::getCapacity() {
  return this->capacity;
}

garbageType Station::getGarbageType() {
  return this->garbage;
}
