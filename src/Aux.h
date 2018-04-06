#ifndef _AUX_H
#define _AUX_H

#include <iostream>

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

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
