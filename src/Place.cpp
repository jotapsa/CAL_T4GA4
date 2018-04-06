#include "Place.h"

Place::Place(unsigned long id) {
    this->id = id;
}

Place::Place(unsigned long id, double dLon, double dLat, double rLon, double rLat, std::pair<int, int> coordinates) {
    this->id = id;

    this->dLon = dLon;
    this->dLat = dLat;
    this->rLon = rLon;
    this->rLat = rLat;

    this->coordinates = coordinates;
}


unsigned long Place::getID() const{
    return this->id;
}

std::pair<double, double> Place::getCoordinates() {
    return this->coordinates;
}

bool Place::operator==(const Place& o){
    return this->id == o.getID();
}
