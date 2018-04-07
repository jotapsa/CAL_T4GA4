
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include <string>
#include "GarbageType.h"
#include "Place.h"

class Garage; //foward declaration

class Vehicle {
private:
    unsigned long int ID;
    Place *place;
    Garage* garage;
    std::string plate;
    GarbageType type;
    double capacity;
    double filled;
public:
    Vehicle(unsigned long int ID, Garage *garage, std::string plate, GarbageType type, double capacity);

    unsigned long int getID();
    Place * getPlace();
    Garage * getGarage();
    std::string getPlate();
    GarbageType getType();
    double getCapacity();
    double getFreeSpace();

    void reset();

    void move(std::pair<int,int> direction);
};


#endif //_VEHICLE_H
