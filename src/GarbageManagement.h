#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include "Graph.h"
#include "Station.h"
#include "Garage.h"
#include "Container.h"
#include "Street.h"

class GarbageManagement{
private:
    Graph<Place> graph;

    std::vector<Container *> containers;
    std::vector<Station *> stations;
    std::vector<Garage *> garages;
    std::vector<Street *> streets;

public:
    GarbageManagement();
    Graph<Place> getGraph();
    std::vector<Container *> getContainers();
    std::vector<Station *> getStations();
    std::vector<Garage *> getGarages();
    std::vector<Street *> getStreets();

    Garage * getGarage(unsigned long garageId);

    void addPlace(Place *place);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageId, Vehicle vehicle);
    void addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type, std::string name);

    virtual ~GarbageManagement();
};

#endif
