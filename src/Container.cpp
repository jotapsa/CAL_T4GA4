#include "Container.h"

Container::Container(Node &node, garbageType type, double capacity) : Place(node){
  this->type = type;
  this->capacity = capacity;
}

garbageType Container::getType() {
  return this->type;
}

double Container::getCapacity() {
  return this->capacity;
}