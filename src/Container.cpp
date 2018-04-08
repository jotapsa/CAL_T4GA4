#include "Container.h"
#include "Aux.h"
#include <sstream>

Container::Container(Place *place, GarbageType type, double capacity){
    this->place = place;
    this->type = type;
    this->capacity = capacity;

    this->dist = double_dist(0, this->capacity);
    this->filled = dist(rng);
}

Container::Container(unsigned long id, double dLon, double dLat, double rLon, double rLat,
                     std::pair<int, int> coordinates, GarbageType type, double capacity){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            coordinates);
    this->type = type;
    this->capacity = capacity;

    this->dist = double_dist(0, this->capacity);
    this->filled = dist(rng);
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

void Container::reset() {
    this->filled = dist(rng);
}

std::string Container::toString() {
    std::stringstream container;

    container << this->place->toString() << ";" << getGarbageType(this->type) << ";" << this->capacity;
    return container.str();
}

void Container::setGarbageType(GarbageType type) {
    this->type = type;
}

void Container::setCapacity(double capacity) {
    this->capacity = capacity;
}

void Container::setFilledPer(double percentage) {
    this->filled = percentage;
}
