#ifndef _STATION_H
#define _STATION_H

#include "Place.h"
#include "Aux.h"


class Station : public Place {
private:
    garbageType type;
    double capacity;
public:Station(unsigned long id, std::pair<double, double> coordinates, garbageType type, double capacity);
    garbageType getGarbageType();
    double getCapacity();
};


#endif //_STATION_H
