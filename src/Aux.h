#ifndef _AUX_H
#define _AUX_H

#include <iostream>

enum GarbageType{
    glass, plastic, paper, generic
};

enum BuildingType{
    container, station, garage, none
};

enum EdgeType{
    twoWay, oneWay
};

void convertToKiloMeters(std::pair<double,double> *longitudinalCoordinates, double rLatitude, double rLongitude);

#endif
