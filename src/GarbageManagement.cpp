#include "GarbageManagement.h"
#include <iostream>

using namespace std;

GarbageManagement::GarbageManagement() {
}

Graph GarbageManagement::getGraph(){
    return this->graph;
}

std::vector<Container> GarbageManagement::getContainers() {
    return this->containers;
}

void GarbageManagement::addNode(Node node) {
    this->graph.addNode(node);
}

void GarbageManagement::addContainer(Container container) {
    this->containers.push_back(container);
//    this->graph.addNode(container);
}

void GarbageManagement::addStation(Station station) {
    this->stations.push_back(station);
//    this->graph.addNode(station);
}

void GarbageManagement::addGarage(Garage garage) {
    this->garages.push_back(garage);
//    this->graph.addNode(garage);
}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}