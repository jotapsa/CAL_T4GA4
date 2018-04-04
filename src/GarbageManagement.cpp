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

//bool GarbageManagement::load(){
//    if(!loadNodes(this->graph)){
//        cout << "Failed to read nodes!" << endl;
//        return false;
//    };
//
//    std::cout << this->graph.getNumNodes() << " nodes were successfully read!\n";
//
////    std::cout << this->graph.getContainers().size() << " containers!\n";
//
//    if(!loadEdges(this->graph)){
//        cout << "Failed to read edges!" << endl;
//        return false;
//    };
//
//    std::cout << this->graph.getStreets().size() << " edges were successfully read!\n";
//
//    if(!loadEdgesInfo(this->graph)){
//        cout << "Failed to read edges info!" << endl;
//        return false;
//    };
//
//    std::cout << this->graph.getStreets().size() << " edges were successfully updated!\n";
//
//    return true;
//}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}