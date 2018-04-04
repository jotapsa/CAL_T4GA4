#include "Street.h"

Street::Street(unsigned long int ID, std::string name, int edgeType){
  this->ID = ID;
  this->roadName = name;
  this->edgeType = edgeType;
}

Street::Street(unsigned long int ID, Node &n1, Node &n2){
  this->ID = ID;
  this->n1 = &n1;
  this->n2 = &n2;
}

unsigned long int Street::getID(){
  return this->ID;
}

std::string Street::getName() {
  return this->roadName;
}

void Street::setName(std::string name){
  this->roadName = name;
}

void Street::setEdgeType(EdgeType type){
  this->edgeType = type;
}

int Street::getEdgeType() {
  return this->edgeType;
}

void Street::addNodes(Node &n1, Node &n2){
  this->n1 = &n1;
  this->n2 = &n2;
}