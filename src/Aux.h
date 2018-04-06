#ifndef _AUX_H
#define _AUX_H

#include <iostream>

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

#define backgroundImgPath "../img/map_background.png"

enum GarbageType{
    glass, plastic, paper, generic
};

enum EdgeType{
    twoWay, oneWay
};

void convertToKilometers(std::pair<double, double> *longitudinalCoordinates, double rLatitude, double rLongitude);

GarbageType getGarbageType(std::string type);
std::string getGarbageType(GarbageType type);

//TODO:
std::pair<int, int> convertToCoords(const std::pair<double, double> coordinates, std::pair<int, int> screenSize);

GarbageType getGarbageTypeForOption(unsigned int option);

#endif
