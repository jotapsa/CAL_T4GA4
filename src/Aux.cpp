#include "Aux.h"

#include <cmath>
#include "Algorithm.h"

GarbageType getGarbageType(std::string type){
    if(type.compare(std::string("glass")) == 0){
        return GarbageType ::glass;
    }
    else if(type.compare(std::string("plastic")) == 0){
        return GarbageType ::plastic;
    }
    else if(type.compare(std::string("paper")) == 0){
        return GarbageType ::paper;
    }
    else if(type.compare(std::string("generic")) == 0){
        return GarbageType ::generic;
    }

    return GarbageType ::generic;
}

std::string getGarbageType(GarbageType type) {
    switch (type) {
        case GarbageType ::glass: {
            return std::string("glass");
        }
        case GarbageType ::plastic: {
            return std::string("plastic");
        }
        case GarbageType ::paper: {
            return std::string("paper");
        }
        default: {
            return std::string("generic");
        }
    }
}

std::string getGarbageTypeImgPath(GarbageType type){
    switch (type) {
        case GarbageType ::glass: {
            return glassImgPath;
        }
        case GarbageType ::plastic: {
            return plasticImgPath;
        }
        case GarbageType ::paper: {
            return paperImgPath;
        }
        default: {
            return genericImgPath;
        }
    }
}

std::string getAlgorithmName(Algorithm type) {

    switch(type) {
        case Algorithm::Dijkstra:
            return std::string("Dijkstra");
        case Algorithm::aStar:
            return std::string("A*");
        case Algorithm::Warshall:
            return std::string("Floyd Warshall");
    }
}

std::string getEdgeType(EdgeType type){
    switch (type) {
        case EdgeType::twoWay: {
            return std::string("True");;
        }
        case EdgeType::oneWay: {
            return std::string("False");
        }
    }
}

double deg2rad(double deg) {
    return deg * (M_PI / 180);
}

double getDistance(double lat1, double lon1, double lat2, double lon2) {
//    https://www.movable-type.co.uk/scripts/latlong.html
    double R = 6371e3;

    double rLat1 = deg2rad(lat1);
    double rLat2 = deg2rad(lat2);

    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(rLat1) * cos(rLat2)
               * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;

    return d; //meters
}

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat) {

    int x = (int)((dLon - MIN_LONGITUDE) * IMAGE_X / DELTA_X);
    int y = (int)(IMAGE_Y - (dLat - MIN_LATITUDE) * IMAGE_Y / DELTA_Y);

    return std::make_pair(x,y);
}

std::pair<int, int> convertToCoords(std::pair<double, double> coords) {

    int x = (int)((coords.second - MIN_LONGITUDE) * IMAGE_X / DELTA_X);
    int y = (int)(IMAGE_Y - (coords.first - MIN_LATITUDE) * IMAGE_Y / DELTA_Y);

    return std::make_pair(x,y);
};

bool insideWindow(std::pair<int, int> coords) {

    return coords.first < IMAGE_X || coords.second < IMAGE_Y;
}

std::pair<int, int> getDirectionPlaces(Place *p1, Place *p2){
    return std::make_pair(p2->getCoordinates().first - p1->getCoordinates().second, p2->getCoordinates().second - p1->getCoordinates().second);
};

