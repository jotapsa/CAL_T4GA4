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
#include "Algorithm.h"
#include <unordered_map>

class GarbageManagement {
private:
    Graph<Place> graph;

    Algorithm algorithm;
    float fillPerNeeded;

    GraphViewer *gv;

    std::vector<Place *> places;
    std::vector<Container *> containers;
    std::vector<Station *> stations;
    std::vector<Garage *> garages;
    std::vector<Street *> streets;
    std::vector<Vehicle *> vehicles;

    std::string mapPath;
    std::string mapName;
    unsigned int imageWidth;
    unsigned int imageHeight;

    double minLat;
    double minLon;
    double maxLat;
    double maxLon;

public:
    GarbageManagement();

    void initGraphViewer();

    Graph<Place> getGraph();

    Algorithm getAlgorithm() const;
    float getFillPerNeeded() const;

    std::vector<Place *> getPlaces() const;
    std::vector<Place *> getEmptyPlaces() const;
    std::vector<Container *> getContainers() const;
    std::vector<Station *> getStations() const;
    std::vector<Garage *> getGarages() const;
    std::vector<Street *> getStreets() const;
    std::vector<Vehicle *> getVehicles() const;
    std::vector<Vehicle *> getVehiclesFromGarage(unsigned long int garageID) const;
    std::vector<std::pair<unsigned long, std::string>> getAllStreetNames();

    Place * getPlace(unsigned long id)const;
    Place * getEmptyPlace(unsigned long id)const;
    Container * getContainer(unsigned long containerID)const;
    Station * getStation(unsigned long stationID)const;
    Garage * getGarage(unsigned long garageID) const;
    Street * getStreet(unsigned long ID) const;
    Street * getStreet(Place *p1, Place *p2) const;
    Vehicle * getVehicle(unsigned long vehicleID) const;
    std::string getMapPath() const;
    std::string getMapName() const;
    std::vector<double> getCoords() const;

    std::vector<Container *> getMatchingContainers(Vehicle *vehicle, std::vector<Container *> containers, bool differentiated);
    Container *getClosestContainerToVehicle(Vehicle *vehicle, std::vector<Container *> containers, bool differentiated);
    Station *getClosestStationToVehicle(Vehicle *pVehicle, std::vector<Station *> vector);

    void setMapPath(std::string mapPath);
    void setMapName(std::string mapName);
    void setCoords(double minLat, double minLon, double maxLat, double maxLon);
    void setAlgorithm(Algorithm algorithm);
    void setFillPerNeeded(float fillPerNeeded);

    void addPlace(Place *place);
    void addContainer(Container *container);
    void addStation(Station *station);
    void addGarage(Garage *garage);
    void addVehicle(unsigned long garageID, Vehicle *vehicle);
    void addVehicleToGraph(Vehicle *vehicle); //add Vehicle to GraphViewer
    void addEdge(double weight, unsigned long int ID, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type, std::string name);

    void removePlace(Place* place);
    void removeEmptyPlace(const unsigned long &ID);
    void removeContainer(const unsigned long &containerID);
    void removeStation(const unsigned long &stationID);
    void removeGarage(const unsigned long &garageID);
    void removeVehicle(const unsigned long &vehicleID);
    void removeVehicleFromGraph(Vehicle *vehicle); //remove Vehicle to GraphViewer
    void removeEdge(const unsigned long &ID);

    void resetContainers();
    void resetVehicles();

    void evalCon();
    void collectGarbage(bool differentiated);

    void rearrange();

    void closeWindow();

    void printResults(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths);

    void resetStreetsGraph();

    void updateBuildingsGraph();

    bool updateVehicle(Vehicle * vehicle, std::vector<Place *> path, std::vector<Street *> streetsVehicle, unsigned int *index);

    void visualFeedback(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths);

    void feedback(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths);

    //Search
    std::vector<Street *> getStreetByName(std::string streetName, bool kmp);
    std::vector<std::pair<Container*, std::string>> getStreetContainers(std::vector<Street *> edges);
    Container* getContainerStreets(std::string firstStreetName, std::string secondStreetName, bool kmp);
    std::string filterNameStreet(std::string streetName);
    std::vector<std::pair<std::string, int>> bestStreets(std::string streetName);
};

#endif
