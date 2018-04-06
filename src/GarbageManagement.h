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
#include "GraphViewer.h"

class GarbageManagement {
private:
    Graph<Place> graph;

    GraphViewer *gv;

    std::vector<Place *> places;
    std::vector<Container *> containers;
    std::vector<Station *> stations;
    std::vector<Garage *> garages;
    std::vector<Street *> streets;

public:
    GarbageManagement();
    Graph<Place> getGraph();


    std::vector<Place *> getPlaces() const;
    std::vector<Place *> getEmptyPlaces() const;
    std::vector<Container *> getContainers() const;
    std::vector<Station *> getStations() const;
    std::vector<Garage *> getGarages() const;
    std::vector<Street *> getStreets() const;
    std::vector<Vehicle *> getVehicles(unsigned long int garageID) const;

    Place *getPlace(unsigned long id);
    Place *getEmptyPlace(unsigned long id);
    Container *getContainer(unsigned long containerID);
    Station *getStation(unsigned long stationID);
    Garage * getGarage(unsigned long garageID) const;

    void addPlace(Place *place);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageID, Vehicle *vehicle);
    void addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type, std::string name);

    void evalCon();

    void rearrange();
    void closeWindow();
};

#endif
