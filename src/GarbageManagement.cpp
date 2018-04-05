#include "GarbageManagement.h"
#include <iostream>
#include <cmath>

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
//     if(!this->graph.addNode(place)){
//         //already exists
//     }
}

void GarbageManagement::addContainer(Container *container) {
    this->containers.push_back(container);
    //addPlace(container->getNode());
}

void GarbageManagement::addStation(Station *station) {
    this->stations.push_back(station);
    //addPlace(station->getNode());
}

void GarbageManagement::addGarage(Garage *garage) {
    this->garages.push_back(garage);
    //addPlace(garage->getNode());
}


Garage * GarbageManagement::getGarage(unsigned long garageId) {
//    for(unsigned int i=0; i<this->garages.size(); i++){
//        if(this->garages[i]->getNode()->getID() == garageId){
//            return garages[i];
//        }
//    }
//    return nullptr;
}


void GarbageManagement::addVehicle(unsigned long garageId, Vehicle vehicle) {
    Garage *garage= this->getGarage(garageId);
    garage->addVehicle(vehicle);
    
}

void GarbageManagement::addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type,
                                std::string name) {
//    Node *sourceNode = graph.getNode(nodeIds.first);
//    Node *destNode = graph.getNode(nodeIds.second);

//    if(sourceNode == nullptr || destNode == nullptr){
//        std::cout << "Couldn't find nodes" << std::endl;
//        return;
//    }

//    if(weight == 0){
//        weight = std::abs(destNode->getCoordinates().first - sourceNode->getCoordinates().first) +
//                 std::abs(destNode->getCoordinates().second - destNode->getCoordinates().second);
//    }

//    if(name.empty()){
//        name = "unnamed street n" + this->streets.size();
//    }

//
//    this->streets.push_back(new Street(sourceNode, destNode, name));
//    this->graph.addEdge(nodeIds.first, nodeIds.second, weight, type);
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
