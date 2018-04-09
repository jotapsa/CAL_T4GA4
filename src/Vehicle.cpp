#include <sstream>
#include <algorithm>
#include "Vehicle.h"
#include "Garage.h"
#include "Aux.h"
#include "Container.h"

Vehicle::Vehicle(unsigned long int ID, Garage *garage, std::string plate, std::vector<GarbageType> types, std::vector<double> capacities) {
    this->ID = ID;
    this->garage = garage;
    this->plate = plate;
    this->types = types;
    this->capacities = capacities;

    this->filled.resize(this->capacities.size(), 0);
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

bool Vehicle::hasType(GarbageType type){
    auto it = std::find(this->types.begin(), this->types.end(), type);
    if(it != this->types.end()){
        return true;
    }
    return false;
}

double Vehicle::getCapacity(GarbageType type) {
    if(hasType(type)){
        auto it = std::find(this->types.begin(), this->types.end(), type);
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
    if(hasType(type)){
        auto it = std::find(this->types.begin(), this->types.end(), type);
        int typeIndex = std::distance(this->types.begin(), it);
        return this->capacities.at(typeIndex)-this->filled.at(typeIndex);
    }
    else{
        return 0;
    }
}

//TODO Sa nao te esquecas, senao estas f*dido :X
void Vehicle::reset() {
    this->place = garage->getPlace();
}

void Vehicle::moveTo(Place *place){
    this->place = place;
}

void Vehicle::loadFromContainer(Container *container) {
    GarbageType containerType = container->getType();
    if(hasType(containerType)){
        auto it = std::find(this->types.begin(), this->types.end(), containerType);
        int typeIndex = std::distance(this->types.begin(), it);
        this->filled.at(typeIndex) += container->getFilled();
        container->resetFilled();
    }
}

void Vehicle::unloadToStation(Station *station) {
    this->filled.resize(this->capacities.size(), 0);
}
