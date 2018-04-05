#ifndef _GARAGE_H
#define _GARAGE_H

#include "Building.h"
#include "Vehicle.h"

class Garage : Building {
    std::vector<Vehicle> vehicles;
public:
    explicit Garage(Node &node);
    Garage(Node &node, std::vector<Vehicle> &vehicles);
    int getNumberOfVehicles();
    int getNumberOfVehiclesOfType(garbageType type);

    void addVehicle(Vehicle vehicle);
};

#endif //_GARAGE_H
