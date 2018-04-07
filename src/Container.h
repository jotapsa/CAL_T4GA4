#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Place.h"
#include "GarbageType.h"

class Container{
private:
    Place *place;
    GarbageType type;
    double capacity;
    double filled;

public:
    Container(Place *place, GarbageType type, double capacity);
    Container(unsigned long id, double dLon, double dLat, double rLon, double rLat,
              std::pair<int, int> coordinates, GarbageType type, double capacity);

    Place* getPlace();
    GarbageType getType();
    double getCapacity();
    double getFilledPer();
    std::string toString();
};

#endif
