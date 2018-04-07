#include "Place.h"
#include <sstream>
#include <iomanip>

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

double Place::getLat(){
    return this->dLat;
}

double Place::getLon(){
    return this->dLon;
}

std::pair<int, int> Place::getCoordinates() {
    return this->coordinates;
}

std::pair<double, double> Place::getLongitudinalCoordinates() {

    return std::make_pair(this->dLon, this->dLat);
};

std::string Place::toString() {
    std::stringstream place;

    place << this->id << ";" << std::setprecision(10) << this->dLon << ";" << this->dLat << ";" << this->rLon << ";" << this->rLat;
    return place.str();
}

bool Place::operator==(const Place& o){
    return this->id == o.getID();
}

unsigned long Place::getUnusedId() {
    return maxId+1;
}
