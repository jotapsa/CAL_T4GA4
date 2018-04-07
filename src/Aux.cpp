#include "Aux.h"

#include <cmath>

using namespace std;

GarbageType getGarbageType(string type){
    if(type.compare(string("glass")) == 0){
        return glass;
    }
    else if(type.compare(string("plastic")) == 0){
        return plastic;
    }
    else if(type.compare(string("paper")) == 0){
        return paper;
    }
    else if(type.compare(string("generic")) == 0){
        return generic;
    }

    return generic;
}

std::string getGarbageType(GarbageType type) {
    switch (type) {
        case glass: {
            return std::string("glass");;
        }
        case plastic: {
            return std::string("plastic");
        }
        case paper: {
            return std::string("paper");
        }
        default: {
            return std::string("generic");
        }
    }
}

GarbageType getGarbageTypeForOption(unsigned int option) {

    static GarbageType types[4] = { glass, plastic, paper, generic };

    return types[option];
}

std::string getEdgeType(EdgeType type){
    switch (type) {
        case twoWay: {
            return std::string("True");;
        }
        case oneWay: {
            return std::string("False");
        }
        default: {
            return std::string();
        }
    }
}

//void convertToKilometers(std::pair<double, double> *longitudinalCoordinates, double rLatitude, double rLongitude) {
//
//    longitudinalCoordinates->first = rLatitude * 110.574;
//    longitudinalCoordinates->second = cos(rLatitude) * 111.320;
//};

//TODO: Duarte tens na header definido a width e height do ecra.
std::pair<int, int> convertToCoords(double dLon, double dLat, double rLon, double rLat) {
    return {};
}
