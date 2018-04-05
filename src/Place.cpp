#include "Place.h"

Place::Place(unsigned long id) {
    this->id = id;
}
Place::Place(unsigned long id, std::pair<double, double> coordinates) {
    this->id = id;
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