#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Aux.h"
#include "Place.h"

class Container : public Place{
private:
    GarbageType type;
    double capacity;
public:
    Container(unsigned long id, std::pair<double, double> coordinates, GarbageType type, double capacity);
    GarbageType getType();
    double getCapacity();
};

#endif
