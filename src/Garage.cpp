#include "Garage.h"
#include "Aux.h"
#include <sstream>

Garage::Garage(Place *place){
    this->place = place;
}

Garage::Garage(unsigned long id, double dLon, double dLat, double rLon, double rLat,
               std::pair<int, int> coordinates){
    this->place = new Place(id,
                            dLon, dLat,
                            rLon, rLat,
                            coordinates);
}

Place* Garage::getPlace(){
    return this->place;
}

unsigned long Garage::getNumberOfVehicles() {
    return this->vehicles.size();
}

int Garage::getNumberOfVehiclesOfType(GarbageType type) {
    int num = 0;

    for(auto v: vehicles) {
        for(GarbageType garbageType : v->getTypes()){
            if(garbageType == type) {
                num++;
            }
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

std::string Garage::toString(){
    std::stringstream garage;

    garage << this->place->toString();
    for(Vehicle *v : this->vehicles){
        garage << ";" << v->getID();
    }
    return garage.str();
}

void Garage::removeVehicle(unsigned long vehicleID) {

    for(auto vehicle = this->vehicles.begin(); vehicle != this->vehicles.end(); vehicle++) {
        if((*vehicle)->getID() == vehicleID) {
            this->vehicles.erase((vehicle));
            return;
        }
    }

    std::cout << "Vehicle with " << vehicleID << " as ID doesn't exist.\n";
}
