
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include <string>
#include "GarbageType.h"
#include "Place.h"

class Vehicle {
private:
    unsigned long int ID;
    Place *place;
    std::string plate;
    GarbageType type;
    double capacity;
    double filled;
public:
    Vehicle(unsigned long int ID, Place *place, std::string plate, GarbageType type, double capacity);

    unsigned long int getID();
    Place* getPlace();
    std::string getPlate();
    GarbageType getType();
    double getCapacity();
    double getFreeSpace();

    void reset();
};


#endif //_VEHICLE_H
