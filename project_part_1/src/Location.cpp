//
// Created by dnc on 31-03-2018.
//

#include "Location.h"


DegreeLocation::DegreeLocation(double lon, double lat) {

  this->dLon = lon;

  this->dLat = lat;
}

double DegreeLocation::getLon() {
  return this->dLon;
}

double DegreeLocation::getLat() {
  return this->dLat;
}

RadiansLocation::RadiansLocation(double lon, double lat) {

  this->rLon = lon;

  this->rLat = lat;
}

double RadiansLocation::getLon() {
  return this->rLon;
}

double RadiansLocation::getLat() {
  return this->rLat;
}

RadiansLocation Location::getLocationInRadians() {
  return this->rLocation;
}

DegreeLocation Location::getLocationInDegrees() {
  return this->dLocation;
}
