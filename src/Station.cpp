#include "Station.h"
#include "Aux.h"
#include <sstream>

Station::Station(Place *place){
    this->place = place;
}

Station::Station(unsigned long id, double dLon , double dLat, double rLon, double rLat,
                 std::pair<int, int> coordinates){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            coordinates);
}


Place* Station::getPlace(){
    return this->place;
}

std::string Station::toString() {
    std::stringstream station;

    station << this->place->toString();
    return station.str();
}