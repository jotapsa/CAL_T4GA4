#include "Aux.h"

#include <cmath>

void convertToKiloMeters(std::pair<double,double> *longitudinalCoordinates, double rLatitude, double rLongitude) {

    longitudinalCoordinates->first = rLatitude * 110.574;
    longitudinalCoordinates->second = cos(rLatitude) * 111.320;
};

GarbageType getGarbageTypeForOption(unsigned int option) {

    static GarbageType types[4] = { glass, plastic, paper, generic };

    return types[option];
}