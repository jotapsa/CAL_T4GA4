#include "Container.h"

Container::Container(unsigned long id, double dLon, double dLat, double rLon, double rLat,
                     std::pair<int, int> coordinates, GarbageType type, double capacity) :
    Place(id, dLon, dLat, rLat, rLon, coordinates){
    this->type = type;
    this->capacity = capacity;
}

GarbageType Container::getType() {
    return this->type;
}

double Container::getCapacity() {
    return this->capacity;
}
