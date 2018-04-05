#include "Station.h"

Station::Station(unsigned long id, std::pair<double, double> coordinates, garbageType type, double capacity)
        : Place(id, coordinates) {
    this->type = type;
    this->capacity = capacity;

}
double Station::getCapacity() {
    return this->capacity;
}

garbageType Station::getGarbageType() {
    return this->type;
}
