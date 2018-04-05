#ifndef _GARAGE_H
#define _GARAGE_H

#include "Place.h"
#include "Vehicle.h"

class Garage : public Place {
    std::vector<Vehicle> vehicles;
public:
    Garage(unsigned long id, std::pair<double, double> coordinates, std::vector<Vehicle> &vehicles)
    Garage(unsigned long id, std::pair<double, double> coordinates);

    unsigned long getNumberOfVehicles();
    int getNumberOfVehiclesOfType(garbageType type);

    void addVehicle(Vehicle vehicle);
};

#endif //_GARAGE_H
