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

//TODO: Change container type to hashmap because we do alot of searching

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

    Place * getPlace(unsigned long id)const;
    Place * getEmptyPlace(unsigned long id)const;
    Container * getContainer(unsigned long containerID)const;
    Station * getStation(unsigned long stationID)const;
    Garage * getGarage(unsigned long garageID) const;
    Street * getStreet(unsigned long ID) const;

    void addPlace(Place *place);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageID, Vehicle *vehicle);
    void addEdge(double weight, unsigned long int ID, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type, std::string name);

    void removeEmptyPlace(const unsigned long &ID);
    void removeContainer(const unsigned long &containerID);
    void removeStation(const unsigned long &stationID);
    void removeGarage(const unsigned long &garageID);
    void removeEdge(const unsigned long &ID);

    void evalCon();

    void rearrange();

    void closeWindow();
};

#endif
