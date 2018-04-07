#include "Station.h"
#include "Aux.h"
#include <sstream>

Station::Station(Place *place, double capacity){
    this->place = place;
    this->capacity = capacity;
}

Station::Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
                 std::pair<int, int> coordinates, double capacity){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            coordinates);
    this->capacity = capacity;
}


Place* Station::getPlace(){
    return this->place;
}

double Station::getCapacity() {
    return this->capacity;
}

std::string Station::toString() {
    std::stringstream station;

    station << this->place->toString() << ";" << this->capacity;
    return station.str();
}