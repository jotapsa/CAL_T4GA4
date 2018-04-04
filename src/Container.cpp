#include "Container.h"

Container::Container(Node &node, garbageType type, double capacity) : Building(node){
//  this->node = node;
  this->type = type;
  this->capacity = capacity;
}

Node* Container::getNode(){
  return this->node;
}

garbageType Container::getType() {
  return this->type;
}

double Container::getCapacity() {
  return this->capacity;
}