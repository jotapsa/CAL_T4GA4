#include "Vehicle.h"

Vehicle::Vehicle(unsigned long int ID, std::string plate, GarbageType type, double capacity) {
    this->ID = ID;
    this->plate = plate;
    this->type = type;
    this->capacity = capacity;
}

unsigned long int Vehicle::getID(){
    return this->ID;
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
