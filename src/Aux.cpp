#include "Aux.h"

#include <cmath>

std::pair<double,double> convertToKiloMeters(std::pair<double,double> longitudinalCoordinates) {

    double LatitudeKm = longitudinalCoordinates.first * 110.574;
    double LongitudeKm = cos(longitudinalCoordinates.second) * 111.320;

    return std::make_pair(LatitudeKm, LongitudeKm);
};