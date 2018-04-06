#include "Station.h"
#include <sstream>

Station::Station(Place *place, GarbageType type, double capacity){
    this->place = place;
    this->type = type;
    this->capacity = capacity;
}

Station::Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
                 std::pair<int, int> coordinates, GarbageType type, double capacity){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            convertToCoords(dLon, dLat,
                                            rLon, rLat));
    this->type = type;
    this->capacity = capacity;
}


Place* Station::getPlace(){
    return this->place;
}

double Station::getCapacity() {
    return this->capacity;
}

GarbageType Station::getGarbageType() {
    return this->type;
}

std::string Station::toString() {
    std::stringstream station;

    //TODO wtf is :: ?
    station << this->place->toString() << ";" << ::getGarbageType(this->type) << ";" << this->capacity;
    return station.str();
}