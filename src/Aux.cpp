#include "Aux.h"

#include <cmath>

void convertToKiloMeters(std::pair<double,double> *longitudinalCoordinates, double rLatitude, double rLongitude) {

    longitudinalCoordinates->first = rLatitude * 110.574;
    longitudinalCoordinates->second = cos(rLatitude) * 111.320;
};