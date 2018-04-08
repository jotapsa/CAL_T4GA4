#include "Place.h"
#include "Aux.h"
#include <sstream>
#include <iomanip>

unsigned long Place::maxId = 0;

Place::Place(unsigned long id, double dLat, double dLon, double rLat, double rLon, std::pair<int, int> coordinates) {
    this->id = id;
    updateMaxID();

    this->dLat = dLat;
    this->dLon = dLon;
    this->rLat = rLat;
    this->rLon = rLon;

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

void Place::setCoordinates(std::pair<int, int> coordinates){
    this->coordinates = coordinates;
}

void Place::setLat(double Latitude) {
    this->dLat = Latitude;
    this->rLat = Latitude * DEG_TO_RAD;
}

void Place::setLon(double Longitude) {
    this->dLon = Longitude;
    this->rLon = Longitude * DEG_TO_RAD;
}

