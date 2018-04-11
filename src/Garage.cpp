#include "Garage.h"
#include "Aux.h"
#include <sstream>

Garage::Garage(Place *place){
    this->place = place;
}

Place* Garage::getPlace(){
    return this->place;
}

unsigned long Garage::getNumberOfVehicles() {
    return this->vehicles.size();
}

std::vector<Vehicle *> Garage::getVehicles(){
    return this->vehicles;
}

void Garage::addVehicle(Vehicle *vehicle) {
    this->vehicles.push_back(vehicle);
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

std::string Garage::toString(){
    std::stringstream garage;

    garage << this->place->toString();
    for(Vehicle *v : this->vehicles){
        garage << ";" << v->getID();
    }
    return garage.str();
}
