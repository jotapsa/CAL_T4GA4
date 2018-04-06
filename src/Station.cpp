#include "Station.h"

Station::Station(unsigned long id, double dLon, double dLat, double rLon, double rLat,
                 std::pair<int, int> coordinates, GarbageType type, double capacity) :
    Place(id, dLon, dLat, rLon, rLat, coordinates){
    this->type = type;
    this->capacity = capacity;
}

double Station::getCapacity() {
    return this->capacity;
}

GarbageType Station::getGarbageType() {
    return this->type;
}
