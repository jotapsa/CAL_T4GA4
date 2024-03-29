
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
    double filledDif;

    bool full;
public:
    Vehicle(unsigned long int ID, Garage *garage, std::string plate, std::vector<GarbageType> types, std::vector<double> capacities);

    unsigned long int getID();
    Place * getPlace();
    Garage * getGarage();
    std::string getPlate();
    std::vector<GarbageType> getTypes();
    bool hasType(GarbageType);
    double getCapacityForType(GarbageType type);
    double getTotalCapacity();
    double getTotalFreeSpace();
    double getFreeSpaceForType(GarbageType type);
    std::string getTypesString();
    std::string getCapacityString();
    std::string getFreeSpaceString();
    bool getFull();

    void setFull(bool full);

    void moveTo(Place *place);
    void loadFromContainer(Container *container, bool differentiated);
    void unloadToStation(Station *station);

    void reset();

    std::string toString();
};


#endif //_VEHICLE_H
