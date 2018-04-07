#include "Aux.h"

#include <cmath>

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
            return std::string("glass");;
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
    double R = 6371;
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2)
               + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon / 2)
                 * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c; // Distance in km
    return d;
}

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat) {

    double distToOriginX = (dLon - MIN_LONGITUDE);
    double distToOriginy = (dLat - MIN_LATITUDE);
    int x = (int)(distToOriginX * windowWidth / abs(DELTA_LONGITUDE));
    int y = (int)(distToOriginy * windowHeight / abs(DELTA_LATITUDE));

    return std::make_pair(x, y);
}
