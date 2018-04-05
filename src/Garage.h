#ifndef _GARAGE_H
#define _GARAGE_H

#include "Place.h"
#include "Vehicle.h"

class Garage : public Place {
    std::vector<Vehicle *> vehicles;
public:
    Garage(unsigned long id, std::pair<double, double> coordinates);

    unsigned long getNumberOfVehicles();
    int getNumberOfVehiclesOfType(GarbageType type);
    std::vector<Vehicle *> getVehicles();

    void addVehicle(Vehicle *vehicle);
};

#endif //_GARAGE_H
