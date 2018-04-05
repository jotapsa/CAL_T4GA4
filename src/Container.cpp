#include "Container.h"

Container::Container(Node *node, GarbageType type, double capacity) : Building(node){
  this->type = type;
  this->capacity = capacity;
}

GarbageType Container::getType() {
  return this->type;
}

double Container::getCapacity() {
  return this->capacity;
}