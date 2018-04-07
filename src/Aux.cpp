#include "Aux.h"

#include <cmath>

using namespace std;

GarbageType getGarbageType(string type){
    if(type.compare(string("glass")) == 0){
        return GarbageType ::glass;
    }
    else if(type.compare(string("plastic")) == 0){
        return GarbageType ::plastic;
    }
    else if(type.compare(string("paper")) == 0){
        return GarbageType ::paper;
    }
    else if(type.compare(string("generic")) == 0){
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

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat) {

    double distToOriginX = (dLon - MIN_LONGITUDE);
    double distToOriginy = (dLat - MIN_LATITUDE);
    int x = (int)(distToOriginX * windowWidth / abs(DELTA_LONGITUDE));
    int y = (int)(distToOriginy * windowHeight / abs(DELTA_LATITUDE));

    return make_pair(x, y);
}
