#include "Container.h"

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
                            convertToCoords(dLon, dLat,
                                            rLon, rLat));
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
