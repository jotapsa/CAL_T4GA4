#include "Vehicle.h"
#include "Garage.h"

Vehicle::Vehicle(unsigned long int ID, Garage *garage, std::string plate, GarbageType type, double capacity) {
    this->ID = ID;
    this->garage = garage;
    this->plate = plate;
    this->type = type;
    this->capacity = capacity;

    this->place = garage->getPlace();
}

unsigned long int Vehicle::getID(){
    return this->ID;
}

Place* Vehicle::getPlace(){
    return this->place;
}

Garage *Vehicle::getGarage() {
    return this->garage;
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
    this->place = garage->getPlace();
}

void Vehicle::move(std::pair<int,int> direction){
    std::pair<int, int> coordinates = this->place->getCoordinates();
    this->place->setCoordinates(std::make_pair(coordinates.first + direction.first, coordinates.second + direction.second));
}
