#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include "Graph.h"
#include "Station.h"
#include "Garage.h"

class GarbageManagement{
private:
    Graph graph;

    std::vector<Container> containers;
    std::vector<Station> stations;
    std::vector<Garage> garages;
public:
    GarbageManagement();
    Graph getGraph();
    std::vector<Container> getContainers();
    std::vector<Station> getStations();
    std::vector<Garage> getGarages();
    Garage getGarage(unsigned long garageId);

    void addNode(Node *node);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageId, Vehicle vehicle);
    void addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type, std::string name);

    virtual ~GarbageManagement();
};

#endif
