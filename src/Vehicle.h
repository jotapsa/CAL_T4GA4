
#ifndef _VEHICLE_H
#define _VEHICLE_H


#include "Aux.h"

class Vehicle {
private:
    unsigned long int ID;
    std::string plate;
    GarbageType type;
    double capacity;
    double filled;
public:
    Vehicle(unsigned long int ID, std::string plate, GarbageType type, double capacity);

    unsigned long int getID();
    std::string getPlate();
    GarbageType getType();
    double getCapacity();
    double getFreeSpace();
};


#endif //_VEHICLE_H
