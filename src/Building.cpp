#include "Building.h"

Building::Building(Node *node) {
  this->node = node;
}

Node* Building::getNode(){
  return this->node;
}