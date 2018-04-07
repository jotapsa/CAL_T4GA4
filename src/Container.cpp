#include "Container.h"
#include "Aux.h"
#include <sstream>

Container::Container(Place *place, GarbageType type, double capacity){
    this->place = place;
    this->type = type;
    this->capacity = capacity;
}

Container::Container(unsigned long id, double dLon, double dLat, double rLon, double rLat,
                     std::pair<int, int> coordinates, GarbageType type, double capacity){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            coordinates);
    this->type = type;
    this->capacity = capacity;
}

Place* Container::getPlace(){
    return this->place;
}

GarbageType Container::getType() {
    return this->type;
}

double Container::getCapacity() {
    return this->capacity;
}

double Container::getFilledPer() {
    return (filled/capacity)*100;
}

std::string Container::toString() {
    std::stringstream container;

    container << this->place->toString() << ";" << getGarbageType(this->type) << ";" << this->capacity;
    return container.str();
}
