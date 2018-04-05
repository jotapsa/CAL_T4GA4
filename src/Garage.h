#ifndef _GARAGE_H
#define _GARAGE_H

#include "Building.h"
#include "Vehicle.h"

class Garage : public Building {
    std::vector<Vehicle> vehicles;
public:
    explicit Garage(Node *node);
    Garage(Node *node, std::vector<Vehicle> &vehicles);
    unsigned long getNumberOfVehicles();
    int getNumberOfVehiclesOfType(garbageType type);

    void addVehicle(Vehicle vehicle);
};

#endif //_GARAGE_H
