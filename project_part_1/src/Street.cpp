//
// Created by dnc on 31-03-2018.
//

#include "Street.h"

Street::Street(unsigned long id, std::string name, bool twoWay){
  this->id = id;
  this->roadName = name;
  this->twoWay = twoWay;
}

unsigned long Street::getId() {
  return this->id;
}

std::string Street::getName() {
  return this->roadName;
}

bool Street::isStreetTwoWay() {
  return this->isStreetTwoWay();
}