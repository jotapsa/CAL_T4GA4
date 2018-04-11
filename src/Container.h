#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Place.h"
#include "GarbageType.h"
#include "RandomEngine.h"

class Container{
private:
    double_dist dist;
    Place *place;
    GarbageType type;
    double capacity;
    double filled;

public:
    Container(Place *place, GarbageType type, double capacity);

    Place* getPlace();
    GarbageType getType();
    void setGarbageType(GarbageType type);
    double getCapacity();
    double getFilled();
    double getFilledPer();

    void setCapacity(double capacity);
    void emptyOut();

    void reset();

    std::string toString();
};

#endif
