#include "Place.h"
#include <sstream>

unsigned long Place::maxId = 0;

Place::Place(unsigned long id, double dLon, double dLat, double rLon, double rLat, std::pair<int, int> coordinates) {
    this->id = id;
    updateMaxID();

    this->dLon = dLon;
    this->dLat = dLat;
    this->rLon = rLon;
    this->rLat = rLat;

    this->coordinates = coordinates;
}

void Place::updateMaxID(){
    if(id > maxId){
        maxId = id;
    }
    return;
}

unsigned long Place::getID() const{
    return this->id;
}

std::pair<int, int> Place::getCoordinates() {
    return this->coordinates;
}

std::string Place::toString() {
    std::stringstream place;

    place << this->id << ";" << this->dLon << ";" << this->dLat << ";" << this->rLon << ";" << this->rLat;
    return place.str();
}

bool Place::operator==(const Place& o){
    return this->id == o.getID();
}

unsigned long Place::getUnusedId() {
    return maxId+1;
}
