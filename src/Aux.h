#ifndef _AUX_H
#define _AUX_H

#include <iostream>

enum GarbageType{
    glass, plastic, paper, generic
};

enum EdgeType{
    twoWay, oneWay
};

void convertToKiloMeters(std::pair<double,double> *longitudinalCoordinates, double rLatitude, double rLongitude);

GarbageType getGarbageType(std::string type);
std::string getGarbageType(GarbageType type);

GarbageType getGarbageTypeForOption(unsigned int option);

#endif
