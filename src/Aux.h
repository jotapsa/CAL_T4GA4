#ifndef _AUX_H
#define _AUX_H

#include <iostream>
#include "GarbageType.h"
#include "EdgeType.h"

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

#define windowHeight 800
#define windowWidth 800

#define MIN_LATITUDE 41.16703
#define MIN_LONGITUDE -8.658848
#define MAX_LATITUDE 41.22523
#define MAX_LONGITUDE -8.596924

#define DELTA_LONGITUDE (MAX_LONGITUDE-MIN_LONGITUDE)
#define DELTA_LATITUDE (MAX_LATITUDE-MIN_LATITUDE)

#define backgroundImgPath "../img/map_background.png"

#define curvedEdges false
#define emptyPlaceNodeSize 1
#define buildingNodeSize 3

GarbageType getGarbageType(std::string type);
std::string getGarbageType(GarbageType type);

std::string getEdgeType(EdgeType type);

//TODO:
double getDistance(double lat1, double lon1, double lat2, double lon2);

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat);

#endif
