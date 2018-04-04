//
// Created by dnc on 31-03-2018.
//

#include "Street.h"

Street::Street(unsigned long id, std::string name, int edgeType){
  this->id = id;
  this->roadName = name;
  this->edgeType = edgeType;
}

unsigned long Street::getId() {
  return this->id;
}

std::string Street::getName() {
  return this->roadName;
}

int Street::getEdgeType() {
  return this->edgeType;
}

void Street::addNodes(Node *n1, Node *n2){
  this->n1 = n1;
  this->n2 = n2;
}