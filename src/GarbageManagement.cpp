#include "GarbageManagement.h"
#include <cmath>
#include <sstream>

GarbageManagement::GarbageManagement() {
}

Graph<Place> GarbageManagement::getGraph(){
    return this->graph;
}

std::vector<Container *> GarbageManagement::getContainers() {
    return this->containers;
}

std::vector<Station *> GarbageManagement::getStations() {
    return this->stations;
}

std::vector<Garage *> GarbageManagement::getGarages() {
    return this->garages;
}

std::vector<Street *> GarbageManagement::getStreets() {
    return this->streets;
}

void GarbageManagement::addPlace(Place *place) {
    this->places.push_back(place);
    if(!this->graph.addNode(*(place))){
        std::cout << "Node " << place->getId() << " already in graph." << std::endl;
    }
}

void GarbageManagement::addContainer(Container *container) {
    this->containers.push_back(container);
    if(!this->graph.addNode(*(container))){
        std::cout << "Node " << container->getId() << " already in graph." << std::endl;
    }
}

void GarbageManagement::addStation(Station *station) {
    this->stations.push_back(station);
    if(!this->graph.addNode(*(station))){
        std::cout << "Node " << station->getId() << " already in graph." << std::endl;
    }
}

void GarbageManagement::addGarage(Garage *garage) {
    this->garages.push_back(garage);
    if(!this->graph.addNode(*(garage))){
        std::cout << "Node " << garage->getId() << " already in graph." << std::endl;
    }
}

Place * GarbageManagement::getPlace(unsigned long id){
    Place *place = getEmptyPlace(id);
    if(place != nullptr){
        return place;
    }

    Container *container = getContainer(id);
    if(container != nullptr){
        return container;
    }

    Station *station = getStation(id);
    if(station != nullptr){
        return station;
    }

    Garage *garage = getGarage(id);
    if(garage != nullptr){
        return garage;
    }
    return nullptr;
}

Place *  GarbageManagement::getEmptyPlace(unsigned long id){
    for(auto p: places){
        if(p->getId() == id){
            return p;
        }
    }
    return nullptr;
}

Container * GarbageManagement::getContainer(unsigned long containerId){
    for(auto c: containers){
        if(c->getId() == containerId){
            return c;
        }
    }
    return nullptr;
}

Station *GarbageManagement::getStation(unsigned long stationId) {
    for(auto s: stations){
        if(s->getId() == stationId){
            return s;
        }
    }
    return nullptr;
}

Garage * GarbageManagement::getGarage(unsigned long garageId) {
    for(auto g: garages){
        if(g->getId() == garageId){
            return g;
        }
    }
    return nullptr;
}


void GarbageManagement::addVehicle(unsigned long garageId, Vehicle *vehicle) {
    Garage *garage= this->getGarage(garageId);
    garage->addVehicle(vehicle);

}

void GarbageManagement::addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type,
                                std::string name) {
    Place *sourceNode = getPlace(nodeIds.first);
    Place *destNode = getPlace(nodeIds.second);

    if(sourceNode == nullptr || destNode == nullptr){
        std::cout << "Couldn't find nodes" << std::endl;
        return;
    }

    if(weight == 0){
        weight = std::abs(destNode->getCoordinates().first - sourceNode->getCoordinates().first) +
                 std::abs(destNode->getCoordinates().second - destNode->getCoordinates().second);
    }

    if(name.empty()){
        std::stringstream strstream;
        strstream << "unnamed street n" << this->streets.size();
        name = strstream.str();
    }


    this->streets.push_back(new Street(sourceNode, destNode, name));
    this->graph.addEdge(nodeIds.first, nodeIds.second, weight, type);
}

//void GarbageManagement::insertNodeAt(double latitude, double longitude) {
//
//    //TODO Refactor
//
//    unsigned long idToInsert = rand() % INF + 1;
//    std::pair<double,double> location;
//    location.first = latitude;
//    location.second = longitude;
//
//    while(this->graph.getNode(idToInsert) != nullptr) {
//        idToInsert = rand() % INF + 1;
//
//        this->graph.addNode(new Node(idToInsert, location));
//
//        std::cout << "Failed adding node with ID: " << idToInsert << std::endl;
//    }
//
//    std::cout << "added node with ID: " << idToInsert << std::endl;
//}

unsigned long GarbageManagement::getValidNodeID() {

    //TODO Refactor

    unsigned long idToInsert = rand() % INF + 1;

    while(this->graph.getNode(Place(idToInsert)) != nullptr) {
        idToInsert = rand() % INF + 1;

        std::cout << idToInsert << " ID already exists!"<< std::endl;
    }

    return idToInsert;
}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}