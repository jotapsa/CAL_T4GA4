#include "GarbageManagement.h"
#include "Aux.h"
#include <cmath>
#include <sstream>

GarbageManagement::GarbageManagement() {
    gv = new GraphViewer(windowWidth, windowHeight, true);
    gv->setBackground(backgroundImgPath);
    gv->createWindow(windowWidth, windowHeight);
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
        if(p->getID() == id){
            return p;
        }
    }
    return nullptr;
}

Container * GarbageManagement::getContainer(unsigned long containerID){
    for(auto c: containers){
        if(c->getID() == containerID){
            return c;
        }
    }
    return nullptr;
}

Station *GarbageManagement::getStation(unsigned long stationID) {
    for(auto s: stations){
        if(s->getID() == stationID){
            return s;
        }
    }
    return nullptr;
}

Garage * GarbageManagement::getGarage(unsigned long garageID) {
    for(auto g: garages){
        if(g->getID() == garageID){
            return g;
        }
    }
    return nullptr;
}

std::vector<Vehicle *> GarbageManagement::getVehicles(unsigned long garageID) {
    Garage *garage= this->getGarage(garageID);
    if(garage != nullptr){
        return garage->getVehicles();
    }
}


void GarbageManagement::addPlace(Place *place) {
    if(!this->graph.addNode(*(place))){
        std::cout << "Node " << place->getID() << " already in graph." << std::endl;
    } else{
        this->places.push_back(place);

//        this->gv->addNode(place->getID(), place->getCoordinates().first, place->getCoordinates().second);
//        this->gv->setVertexColor(place->getID(), BLUE);
//        this->gv->rearrange();
    }
}

void GarbageManagement::addContainer(Container *container) {
    if(!this->graph.addNode(*(container))){
        std::cout << "Node " << container->getID() << " already in graph." << std::endl;
    } else{
        this->containers.push_back(container);

//        this->gv->addNode(container->getID(), container->getCoordinates().first, container->getCoordinates().second);
//        this->gv->setVertexColor(container->getID(), RED);
//        this->gv->rearrange();
    }
}

void GarbageManagement::addStation(Station *station) {
    if(!this->graph.addNode(*(station))){
        std::cout << "Node " << station->getID() << " already in graph." << std::endl;
    } else{
        this->stations.push_back(station);

//        this->gv->addNode(station->getID(), station->getCoordinates().first, station->getCoordinates().second);
//        this->gv->setVertexColor(station->getID(), GREEN);
//        this->gv->rearrange();
    }
}

void GarbageManagement::addGarage(Garage *garage) {
    if(!this->graph.addNode(*(garage))){
        std::cout << "Node " << garage->getID() << " already in graph." << std::endl;
    } else{
        this->garages.push_back(garage);

//        this->gv->addNode(garage->getID(), garage->getCoordinates().first, garage->getCoordinates().second);
//        this->gv->setVertexColor(garage->getID(), BLACK);
//        this->gv->rearrange();
    }
}

//TODO: redo this function, how it works is beyond me
void GarbageManagement::addEdge(double weight, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type,
                                std::string name) {
    Place *sourceNode = getPlace(nodeIDs.first);
    Place *destNode = getPlace(nodeIDs.second);

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

    Street *street = new Street(sourceNode, destNode, name);
    this->streets.push_back(street);
    //this->graph.addEdge(sourceNode, destNode, weight, type);

    //this->gv->addEdge(street->getID(), street->getCoordinates().first, garage->getCoordinates().second);
    //this->gv->setEdgeLabel(street->getID(), street->getName());
    //this->gv->rearrange();
}

void GarbageManagement::addVehicle(unsigned long garageID, Vehicle *vehicle) {
    Garage *garage= this->getGarage(garageID);
    if(garage != nullptr){
        garage->addVehicle(vehicle);
    }
}

unsigned long GarbageManagement::getValidNodeID() {

    //TODO Refactor

    unsigned long idToInsert = rand() % INF + 1;

    while(this->graph.getNode(Place(idToInsert)) != nullptr) {
        idToInsert = rand() % INF + 1;

        std::cout << idToInsert << " ID already exists!"<< std::endl;
    }

    return idToInsert;
}

void GarbageManagement::evalCon() {

}

void GarbageManagement::closeWindow() {
    if(gv != nullptr){
        gv->closeWindow();
    }
}
