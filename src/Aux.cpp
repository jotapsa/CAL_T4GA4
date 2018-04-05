//
// Created by dnc on 05-04-2018.
//

#include "Aux.h"


std::pair<double,double> convertToKiloMeters(std::pair<double,double> longitudinalCoordinates) {

    double LatitudeKm = longitudinalCoordinates.first * 110.574;
    double LongitudeKm = cos(longitudinalCoordinates.second) * 111.320;

    return std::make_pair(LatitudeKm, LongitudeKm);
};