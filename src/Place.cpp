#include "Place.h"

Place::Place(unsigned long id, std::pair<double, double> coordinates) {
    this->id = id;
    this->coordinates = coordinates;
}

unsigned long Place::getId() {
    return this->id;
}

std::pair<double, double> Place::getCoordinates() {
    return this->coordinates;
}
