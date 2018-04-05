#ifndef _STATION_H
#define _STATION_H

#include "Place.h"
#include "Aux.h"


class Station : public Place {
private:
    GarbageType type;
    double capacity;
public:Station(unsigned long id, std::pair<double, double> coordinates, GarbageType type, double capacity);
    GarbageType getGarbageType();
    double getCapacity();
};


#endif //_STATION_H
