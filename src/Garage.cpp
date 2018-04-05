#include "Garage.h"

Garage::Garage(unsigned long id, std::pair<double, double> coordinates) : Place(id, coordinates) {}

unsigned long Garage::getNumberOfVehicles() {
    return this->vehicles.size();
}

int Garage::getNumberOfVehiclesOfType(GarbageType type) {
    int num = 0;

    for(auto v: vehicles) {
        if(v->getType() == type) {
            num++;
        }
    }

    return num;
}

void Garage::addVehicle(Vehicle *vehicle) {
    this->vehicles.push_back(vehicle);
}

std::vector<Vehicle *> Garage::getVehicles(){
    return this->vehicles;
}

