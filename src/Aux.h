#ifndef _AUX_H
#define _AUX_H

#include <iostream>
#include "GarbageType.h"
#include "EdgeType.h"

#define DEFAULT_ALGORITHM 0
#define DEFAULT_FILL_PER_NEEDED 0.75

#define MAX_DOUBLE_WITH 21
#define MAX_ULONG_WITH 10

#define windowHeight 800
#define windowWidth 800

#define PI 3.14159265358979323846
#define MIN_LATITUDE 41.17891
#define MIN_LONGITUDE -8.64511
#define MAX_LATITUDE 41.19311
#define MAX_LONGITUDE -8.62002
#define DELTA_X 0.02509
#define DELTA_Y 0.014199
#define IMAGE_X 2341
#define IMAGE_Y 1760
#define DEG_TO_RAD (PI/180)

#define DELTA_LONGITUDE (MAX_LONGITUDE-MIN_LONGITUDE)
#define DELTA_LATITUDE (MAX_LATITUDE-MIN_LATITUDE)

#define backgroundImgPath "../img/map_background.png"

#define curvedEdges false
#define emptyPlaceNodeSize 1
#define buildingNodeSize 3

GarbageType getGarbageType(std::string type);

std::string getGarbageType(GarbageType type);

std::string getEdgeType(EdgeType type);

double getDistance(double lat1, double lon1, double lat2, double lon2);

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat);

std::pair<int, int> convertToCoords(std::pair<double, double> coords);

bool insideWindow(std::pair<int, int> coords);

#endif
