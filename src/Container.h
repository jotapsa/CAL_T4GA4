#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Aux.h"
#include "Building.h"

class Container : public Building{
private:
    GarbageType type;
    double capacity;
public:
    Container(Node *node, GarbageType type, double capacity);
    GarbageType getType();
    double getCapacity();
};

#endif
