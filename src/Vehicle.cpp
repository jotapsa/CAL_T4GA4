#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, GarbageType type, double capacity) {
    this->plate = plate;
    this->type = type;
    this->capacity = capacity;
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
