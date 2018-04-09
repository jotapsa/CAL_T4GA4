
#ifndef _VEHICLE_H
#define _VEHICLE_H

#include <string>
#include "GarbageType.h"
#include "Place.h"

class Garage; //foward declaration
class Container;
class Station;

class Vehicle {
private:
    unsigned long int ID;
    Place *place;
    Garage* garage;
    std::string plate;
    std::vector<GarbageType> types;
    std::vector<double> capacities;
    std::vector<double> filled;
public:
    Vehicle(unsigned long int ID, Garage *garage, std::string plate, std::vector<GarbageType> types, std::vector<double> capacities);

    unsigned long int getID();
    Place * getPlace();
    Garage * getGarage();
    std::string getPlate();
    std::vector<GarbageType> getTypes();
    bool hasType(GarbageType);
    double getCapacity(GarbageType type);
    double getFreeSpace(GarbageType type);
    std::string getTypesString();
    std::string getCapacityString();
    std::string getFreeSpaceString();

    void moveTo(Place *place);
    void loadFromContainer(Container *container);
    void unloadToStation(Station *station);

    void reset();

    std::string toString();
};


#endif //_VEHICLE_H
