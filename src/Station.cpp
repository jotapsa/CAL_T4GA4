#include "Station.h"

Station::Station(unsigned long id, std::pair<double, double> coordinates, GarbageType type, double capacity)
        : Place(id, coordinates) {
    this->type = type;
    this->capacity = capacity;

}
double Station::getCapacity() {
    return this->capacity;
}

GarbageType Station::getGarbageType() {
    return this->type;
}
