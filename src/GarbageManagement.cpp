#include "GarbageManagement.h"
#include <iostream>

GarbageManagement::GarbageManagement() {
}

Graph GarbageManagement::getGraph(){
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

void GarbageManagement::addNode(Node *node) {
     if(!this->graph.addNode(node)){
         //node already exists in graph
     }
}

void GarbageManagement::addContainer(Container *container) {
    this->containers.push_back(container);
//    this->graph.addNode(container);
}

void GarbageManagement::addStation(Station *station) {
    this->stations.push_back(station);
//    this->graph.addNode(station);
}

void GarbageManagement::addGarage(Garage *garage) {
    this->garages.push_back(garage);
//    this->graph.addNode(garage);
}


Garage * GarbageManagement::getGarage(unsigned long garageId) {
    for(unsigned int i=0; i<this->garages.size(); i++){
        if(this->garages[i]->getNode()->getID() == garageId){
            return garages[i];
        }
    }
    return nullptr;
}


void GarbageManagement::addVehicle(unsigned long garageId, Vehicle vehicle) {
    Garage *garage= this->getGarage(garageId);
    garage->addVehicle(vehicle);
    
}

void GarbageManagement::addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type) {

}

void GarbageManagement::addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIds, EdgeType type,
                                std::string name) {

}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}