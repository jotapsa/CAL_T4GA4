#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include <cstdlib>
#include <ctime>
#include <limits>
#include "Graph.h"
#include "Station.h"
#include "Garage.h"
#include "Container.h"
#include "Street.h"

#define INF std::numeric_limits<unsigned long>::max() //For knowing the limits of nodeID

class GarbageManagement {
private:
    Graph<Place> graph;

    std::vector<Place *> places;
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
    std::vector<Vehicle *> getVehicles(unsigned long int garageID);

    Place *getPlace(unsigned long id);
    Place *getEmptyPlace(unsigned long id);
    Container *getContainer(unsigned long containerID);
    Station *getStation(unsigned long stationID);
    Garage * getGarage(unsigned long garageID);

    void addPlace(Place *place);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageID, Vehicle *vehicle);
    void addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type, std::string name);
    unsigned long getValidNodeID();

    void evalCon();
};

#endif
