#ifndef _AUX_H
#define _AUX_H

#include <iostream>
#include "GarbageType.h"
#include "EdgeType.h"

//TODO: Remove includes in other classes that might import this header to make up for importing enum classes

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

#define graphViewerPort 8123

#define windowHeight 800
#define windowWidth 800

#define MIN_LATITUDE 41.16703
#define MIN_LONGITUDE -8.658848
#define MAX_LATITUDE 41.22523
#define MAX_LONGITUDE -8.596924

#define DELTA_LONGITUDE (MAX_LONGITUDE-MIN_LONGITUDE)
#define DELTA_LATITUDE (MAX_LATITUDE-MIN_LATITUDE)

#define backgroundImgPath "../img/map_background.png"

GarbageType getGarbageType(std::string type);
std::string getGarbageType(GarbageType type);

std::string getEdgeType(EdgeType type);

//TODO:
std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat);

GarbageType getGarbageTypeForOption(unsigned int option);

#endif
