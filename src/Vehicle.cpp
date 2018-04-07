#include "Vehicle.h"

Vehicle::Vehicle(unsigned long int ID, Place *place, std::string plate, GarbageType type, double capacity) {
    this->ID = ID;
    this->place = place;
    this->plate = plate;
    this->type = type;
    this->capacity = capacity;
}

unsigned long int Vehicle::getID(){
    return this->ID;
}

Place* Vehicle::getPlace(){
    return this->place;
}

std::string Vehicle::getPlate() {
    return this->plate;
}

GarbageType Vehicle::getType() {
    return this->type;
}

double Vehicle::getCapacity() {
    return this->capacity;
}

double Vehicle::getFreeSpace() {
    return this->capacity-this->filled;
}

void Vehicle::reset() {
    this->filled = 0;
    //TODO: change currplace to garage
}
