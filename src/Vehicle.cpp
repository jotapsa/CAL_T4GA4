#include <sstream>
#include <algorithm>
#include "Vehicle.h"
#include "Garage.h"
#include "Aux.h"

Vehicle::Vehicle(unsigned long int ID, Garage *garage, std::string plate, std::vector<GarbageType> types, std::vector<double> capacities) {
    this->ID = ID;
    this->garage = garage;
    this->plate = plate;
    this->types = types;
    this->capacities = capacities;

    reset();
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

std::vector<GarbageType> Vehicle::getTypes() {
    return this->types;
}

double Vehicle::getCapacity(GarbageType type) {
    auto it = std::find(this->types.begin(), this->types.end(), type);
    if(it != this->types.end()){
        int typeIndex = std::distance(this->types.begin(), it);
        return this->capacities.at(typeIndex);
    }
    else{
        return 0;
    }
}

std::string Vehicle::toString() {
    std::stringstream vehicle;

    vehicle << this->ID << ";" << this->plate;
    for(int i=0; i < this->types.size(); i++){
        vehicle << ";" << getGarbageType(this->types.at(i));
        vehicle << ";" << this->capacities.at(i);
    }

    return vehicle.str();
}

std::string Vehicle::getTypesString(){
    std::stringstream types;

    for(GarbageType type : this->types){
        types << getGarbageType(type) << "|";
    }

    return types.str().substr(0, types.str().size()-1);
}

std::string Vehicle::getCapacityString(){
    std::stringstream capacities;

    for(double capacity : this->capacities){
        capacities << capacity << "|";
    }

    return capacities.str().substr(0, capacities.str().size()-1);
}

std::string Vehicle::getFreeSpaceString(){
    std::stringstream freeSpaces;

    for(int i=0; i < this->capacities.size(); i++){
        freeSpaces << (this->capacities.at(i)-this->filled.at(i)) << "|";
    }

    return freeSpaces.str().substr(0, freeSpaces.str().size()-1);
}

double Vehicle::getFreeSpace(GarbageType type) {
    auto it = std::find(this->types.begin(), this->types.end(), type);
    if(it != this->types.end()){
        int typeIndex = std::distance(this->types.begin(), it);
        return this->capacities.at(typeIndex)-this->filled.at(typeIndex);
    }
    else{
        return 0;
    }
}

void Vehicle::reset() {
    this->filled.resize(this->capacities.size(), 0);

    this->place = garage->getPlace();
}

void Vehicle::move(std::pair<int,int> direction){
    std::pair<int, int> coordinates = this->place->getCoordinates();
    this->place->setCoordinates(std::make_pair(coordinates.first + direction.first, coordinates.second + direction.second));
}
