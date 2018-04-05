#include "Container.h"


Container::Container(unsigned long id, std::pair<double, double> coordinates,GarbageType type, double capacity) :
        Place(id, coordinates){
    this->type = type;
    this->capacity = capacity;
}

GarbageType Container::getType() {
    return this->type;
}

double Container::getCapacity() {
    return this->capacity;
}