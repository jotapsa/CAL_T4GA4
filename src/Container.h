#ifndef _CONTAINER_H
#define _CONTAINER_H


#include "Aux.h"
#include "Node.h"

class Container{
private:
  Node *node;
  garbageType type;
  double capacity;
public:
  Container(Node &node, garbageType type, double capacity);
  garbageType getType();
  double getCapacity();
};

#endif
