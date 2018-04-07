#ifndef _STATION_H
#define _STATION_H

#include "Place.h"
#include "GarbageType.h"

class Station {
private:
    Place *place;
    double capacity;
public:
    Station(Place *place, double capacity);
    Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
            std::pair<int, int> coordinates, double capacity);

    Place* getPlace();
    double getCapacity();
    std::string toString();
};


#endif //_STATION_H
