#include "Garage.h"

Garage::Garage(Node *node) : Building(node) {
}


Garage::Garage(Node *node, std::vector<Vehicle> &vehicles) : Building(node) {
    this->vehicles = vehicles;
}

unsigned long Garage::getNumberOfVehicles() {
    return this->vehicles.size();
}

int Garage::getNumberOfVehiclesOfType(GarbageType type) {
    int num = 0;

    for(auto truck: vehicles) {
        if(truck.getType() == type) {
            num++;
        }
    }

    return num;
}

void Garage::addVehicle(Vehicle vehicle) {
    this->vehicles.push_back(vehicle);
}


