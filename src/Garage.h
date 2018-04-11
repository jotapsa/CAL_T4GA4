#ifndef _GARAGE_H
#define _GARAGE_H

#include "Place.h"
#include "Vehicle.h"

class Garage{
private:
    Place *place;
    std::vector<Vehicle *> vehicles;
public:
    Garage(Place *place);

    Place* getPlace();
    unsigned long getNumberOfVehicles();
    std::vector<Vehicle *> getVehicles();

    void addVehicle(Vehicle *vehicle);
    void removeVehicle(unsigned long vehicleID);

    std::string toString();
};

#endif //_GARAGE_H
