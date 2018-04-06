#include "Garage.h"

Garage::Garage(unsigned long id, double dLon, double dLat, double rLon, double rLat, std::pair<int, int> coordinates)
    : Place(id, dLon, dLat, rLon, rLat, coordinates) {}

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
