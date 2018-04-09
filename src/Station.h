#ifndef _STATION_H
#define _STATION_H

#include "Place.h"
#include "GarbageType.h"

class Station {
private:
    Place *place;
public:
    explicit Station(Place *place);
    Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
            std::pair<int, int> coordinates);

    Place* getPlace();
    std::string toString();
};


#endif //_STATION_H
