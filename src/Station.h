#ifndef _STATION_H
#define _STATION_H

#include "Place.h"
#include "Aux.h"

class Station {
private:
    Place *place;
    GarbageType type;
    double capacity;
public:
    Station(Place *place, GarbageType type, double capacity);
    Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
            std::pair<int, int> coordinates, GarbageType type, double capacity);

    Place* getPlace();
    GarbageType getGarbageType();
    double getCapacity();
};


#endif //_STATION_H
