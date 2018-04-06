#ifndef _AUX_H
#define _AUX_H

#include <iostream>

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

#define graphViewerPort 8123

#define windowHeight 800
#define windowWidth 800

#define backgroundImgPath "../img/map_background.png"

enum GarbageType{
    glass, plastic, paper, generic
};

enum EdgeType{
    twoWay, oneWay
};

GarbageType getGarbageType(std::string type);
std::string getGarbageType(GarbageType type);

//TODO:
std::pair<int, int> convertToCoords(double dLon, double dLat, double rLon, double rLat);

GarbageType getGarbageTypeForOption(unsigned int option);

#endif
