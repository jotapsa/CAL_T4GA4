//
// Created by dnc on 31-03-2018.
//

#include "Location.h"


Location::Location(double dLon, double dLat, double rLon, double rLat){

  this->dLon = dLon;

  this->dLat = dLat;

  this->rLon = rLon;

  this->rLat = rLat;
}

double Location::getLatitudeInDegrees() {
  return this->dLat;
}

double Location::getLongitudeInDegrees() {
  return this->dLon;
}
