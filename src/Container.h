#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Aux.h"
#include "Place.h"

class Container : public Place{
private:
  garbageType type;
  double capacity;
public:
  Container(Node &node, garbageType type, double capacity);
  garbageType getType();
  double getCapacity();
};

#endif
