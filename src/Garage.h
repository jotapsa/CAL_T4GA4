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
    Garage(unsigned long id, double dLon, double dLat, double rLon, double rLat,
           std::pair<int, int> coordinates);

    Place* getPlace();
    unsigned long getNumberOfVehicles();
    int getNumberOfVehiclesOfType(GarbageType type);
    std::vector<Vehicle *> getVehicles();

    void addVehicle(Vehicle *vehicle);
};

#endif //_GARAGE_H
