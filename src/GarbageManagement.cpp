#include "GarbageManagement.h"
#include "Aux.h"
#include <cmath>
#include <sstream>

GarbageManagement::GarbageManagement() {
//    gv = new GraphViewer(windowWidth, windowHeight, false, graphViewerPort);
//    gv->setBackground(backgroundImgPath);
//    gv->createWindow(windowWidth, windowHeight);
}

Graph<Place> GarbageManagement::getGraph(){
    return this->graph;
}

std::vector<Place *> GarbageManagement::getPlaces() const{
    auto allPlaces = getEmptyPlaces();
    auto containers = getContainers();
    auto stations = getStations();
    auto garages = getGarages();

    for(auto c: containers){
        allPlaces.push_back(c->getPlace());
    }

    for(auto s: stations){
        allPlaces.push_back(s->getPlace());
    }

    for(auto g: garages){
        allPlaces.push_back(g->getPlace());
    }

    return allPlaces;
}

std::vector<Place *> GarbageManagement::getEmptyPlaces() const{
    return this->places;
}

std::vector<Container *> GarbageManagement::getContainers() const{
    return this->containers;
}

std::vector<Station *> GarbageManagement::getStations() const{
    return this->stations;
}

std::vector<Garage *> GarbageManagement::getGarages() const{
    return this->garages;
}

std::vector<Street *> GarbageManagement::getStreets() const{
    return this->streets;
}

Place * GarbageManagement::getPlace(unsigned long id)const {
    Place *place = getEmptyPlace(id);
    if(place != nullptr){
        return place;
    }

    Container *container = getContainer(id);
    if(container != nullptr){
        return container->getPlace();
    }

    Station *station = getStation(id);
    if(station != nullptr){
        return station->getPlace();
    }

    Garage *garage = getGarage(id);
    if(garage != nullptr){
        return garage->getPlace();
    }

    return nullptr;
}

Place * GarbageManagement::getEmptyPlace(unsigned long id)const {
    for(auto p: places){
        if(p->getID() == id){
            return p;
        }
    }
    return nullptr;
}

Container * GarbageManagement::getContainer(unsigned long containerID)const {
    for(auto c: containers){
        if(c->getPlace()->getID() == containerID){
            return c;
        }
    }
    return nullptr;
}

Station * GarbageManagement::getStation(unsigned long stationID)const {
    for(auto s: stations){
        if(s->getPlace()->getID() == stationID){
            return s;
        }
    }
    return nullptr;
}

Garage* GarbageManagement::getGarage(unsigned long garageID) const{
    for(auto g: garages){
        if(g->getPlace()->getID() == garageID){
            return g;
        }
    }
    return nullptr;
}

std::vector<Vehicle *> GarbageManagement::getVehicles(unsigned long garageID) const{
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
    }
}

void GarbageManagement::addContainer(Container *container) {
    if(!this->graph.addNode(*(container->getPlace()))){
        std::cout << "Node " << container->getPlace()->getID() << " already in graph." << std::endl;
    } else{
        this->containers.push_back(container);

//        this->gv->addNode(container->getID(), container->getCoordinates().first, container->getCoordinates().second);
//        this->gv->setVertexColor(container->getID(), RED);
    }
}

void GarbageManagement::addStation(Station *station) {
    if(!this->graph.addNode(*(station->getPlace()))){
        std::cout << "Node " << station->getPlace()->getID() << " already in graph." << std::endl;
    } else{
        this->stations.push_back(station);

//        this->gv->addNode(station->getID(), station->getCoordinates().first, station->getCoordinates().second);
//        this->gv->setVertexColor(station->getID(), GREEN);
    }
}

void GarbageManagement::addGarage(Garage *garage) {
    if(!this->graph.addNode(*(garage->getPlace()))){
        std::cout << "Node " << garage->getPlace()->getID() << " already in graph." << std::endl;
    } else{
        this->garages.push_back(garage);

//        this->gv->addNode(garage->getID(), garage->getCoordinates().first, garage->getCoordinates().second);
//        this->gv->setVertexColor(garage->getID(), BLACK);
    }
}

void GarbageManagement::addEdge(double weight, unsigned long int ID, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type,
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
        strstream << "unnamed street n" << ID;
        name = strstream.str();
    }

    if(!this->graph.addEdge(*(sourceNode), *(destNode), weight, type)){
        std::cout << "Error: Cannot add edge." << std::endl;
    } else{
        Street *street = new Street(ID, sourceNode, destNode, name, type);
        this->streets.push_back(street);
    }

    //this->gv->addEdge(street->getID(), street->getCoordinates().first, garage->getCoordinates().second);
    //this->gv->setEdgeLabel(street->getID(), street->getName());
}

void GarbageManagement::addVehicle(unsigned long garageID, Vehicle *vehicle) {
    Garage *garage= this->getGarage(garageID);
    if(garage != nullptr){
        garage->addVehicle(vehicle);
    }
    else{
        std::cout << "Error: Couldn't find garage" << std::endl;
    }
}

void GarbageManagement::evalCon() {

}

void GarbageManagement::rearrange() {
//    gv->rearrange();
}


void GarbageManagement::closeWindow() {
    if(gv != nullptr){
        gv->closeWindow();
    }
}

void GarbageManagement::removeEmptyPlace(const unsigned long &ID) {
    Place *p = getEmptyPlace(ID);

    //remove from graph

    //remove from container
}

void GarbageManagement::removeStation(const unsigned long &stationID) {
    Station *s = getStation(stationID);

}

void GarbageManagement::removeContainer(const unsigned long &containerID) {
    Container *c = getContainer(containerID);
}

void GarbageManagement::removeGarage(const unsigned long &garageID) {
    Garage *g = getGarage(garageID);

}
