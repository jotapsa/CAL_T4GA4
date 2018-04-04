#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Aux.h"
#include "Building.h"

class Container : public Building{
private:
    Node* node;
  garbageType type;
  double capacity;

public:
  Container(Node &node, garbageType type, double capacity);
  garbageType getType();
  double getCapacity();
};

#endif
