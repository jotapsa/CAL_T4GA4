#include "GarbageManagement.h"
#include "Aux.h"
#include <sstream>

GarbageManagement::GarbageManagement() {
    this->algorithm = static_cast<Algorithm>(DEFAULT_ALGORITHM);
    this->fillPerNeeded = DEFAULT_FILL_PER_NEEDED;

    gv = new GraphViewer(windowWidth, windowHeight, false);
    gv->setBackground(backgroundImgPath);
    gv->createWindow(windowWidth, windowHeight);
    gv->defineEdgeCurved(curvedEdges);
    gv->defineVertexSize(emptyPlaceNodeSize);
}

Algorithm GarbageManagement::getAlgorithm() const {
    return this->algorithm;
}

float GarbageManagement::getFillPerNeeded() const {
    return this->fillPerNeeded;
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

std::vector<Container *> GarbageManagement::getContainersByType(GarbageType type) const {
    std::vector<Container *>  containers;

    auto allContainers = getContainers();
    for(auto c: allContainers){
        if(c->getType() == type){
            containers.push_back(c);
        }
    }

    return containers;
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

std::vector<Vehicle *> GarbageManagement::getAllVehicles() const {
    std::vector<Vehicle *> vehicles;
    auto garages = getGarages();

    for(auto g: garages){
        std::vector<Vehicle *> vehiclesInGarage;
        for(auto v: vehiclesInGarage){
            vehicles.push_back(v);
        }
    }

    return vehicles;
}

std::vector<Vehicle *> GarbageManagement::getVehicles(unsigned long garageID) const{
    Garage *garage= this->getGarage(garageID);
    if(garage != nullptr){
        return garage->getVehicles();
    }
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

//TODO:
Street *GarbageManagement::getStreet(unsigned long ID) const {
    for(auto s: streets){
        if(s->getID() == ID){
            return s;
        }
    }
    return nullptr;
}

void GarbageManagement::setAlgorithm(Algorithm algorithm) {
    this->algorithm = algorithm;
}

void GarbageManagement::setFillPerNeeded(float fillPerNeeded) {
    this->fillPerNeeded = fillPerNeeded;
}

void GarbageManagement::addPlace(Place *place) {
    if(!this->graph.addNode(*(place))){
        std::cout << "Node " << place->getID() << " already in graph." << std::endl;
        return;
    }
    this->places.push_back(place);

    this->gv->addNode((int) place->getID(),
                      place->getCoordinates().first,
                      place->getCoordinates().second);
    this->gv->setVertexColor((int) place->getID(), BLUE);

//    std::stringstream ss;
//    ss << place->getID();
//    this->gv->setVertexLabel((int) place->getID(), ss.str());
    this->gv->setVertexSize((int) place->getID(), emptyPlaceNodeSize);
}

void GarbageManagement::addContainer(Container *container) {
    if(!this->graph.addNode(*(container->getPlace()))){
        std::cout << "Node " << container->getPlace()->getID() << " already in graph." << std::endl;
        return;
    }
    this->containers.push_back(container);

    this->gv->addNode((int) container->getPlace()->getID(),
                      container->getPlace()->getCoordinates().first,
                      container->getPlace()->getCoordinates().second);
//    this->gv->setVertexColor((int) container->getPlace()->getID(), RED);
    this->gv->setVertexIcon((int) container->getPlace()->getID(), getGarbageTypeImgPath(container->getType()));
//        this->gv->setVertexSize((int) container->getPlace()->getID(), buildingNodesSize);
}

void GarbageManagement::addStation(Station *station) {
    if(!this->graph.addNode(*(station->getPlace()))){
        std::cout << "Node " << station->getPlace()->getID() << " already in graph." << std::endl;
        return;
    }
    this->stations.push_back(station);

    this->gv->addNode((int) station->getPlace()->getID(),
                      station->getPlace()->getCoordinates().first,
                      station->getPlace()->getCoordinates().second);
//    this->gv->setVertexColor((int) station->getPlace()->getID(), GREEN);
//        this->gv->setVertexSize((int) station->getPlace()->getID(), buildingNodeSize);
    this->gv->setVertexIcon((int) station->getPlace()->getID(), stationImgPath);
}

void GarbageManagement::addGarage(Garage *garage) {
    if(!this->graph.addNode(*(garage->getPlace()))){
        std::cout << "Node " << garage->getPlace()->getID() << " already in graph." << std::endl;
        return;
    }
    this->garages.push_back(garage);

    this->gv->addNode((int) garage->getPlace()->getID(),
                      garage->getPlace()->getCoordinates().first,
                      garage->getPlace()->getCoordinates().second);
//    this->gv->setVertexColor((int) garage->getPlace()->getID(), YELLOW);
    this->gv->setVertexIcon((int) garage->getPlace()->getID(), garageImgPath);
//        this->gv->setVertexSize((int) garage->getPlace()->getID(), buildingNodeSize);
}

void GarbageManagement::addEdge(double weight, unsigned long int ID, std::pair<unsigned long, unsigned long> nodeIDs, EdgeType type,
                                std::string name) {
    Place *sourceNode = getPlace(nodeIDs.first);
    Place *destNode = getPlace(nodeIDs.second);

    if(sourceNode == nullptr || destNode == nullptr){
        std::cout << "Couldn't find nodes." << std::endl;
        return;
    }

    if(weight == 0){
        weight = getDistance(sourceNode->getLat(), sourceNode->getLon(),
                             destNode->getLat(), destNode->getLon());
    }

//    if(name.empty()){
//        std::stringstream strstream;
//        strstream << "unnamed street n" << ID;
//        name = strstream.str();
//    }

    if(!this->graph.addEdge(*(sourceNode), *(destNode), weight, type)){
        std::cout << "Error: Cannot add edge." << std::endl;
        return;
    }

    Street *street = new Street(ID, sourceNode, destNode, name, type);
    this->streets.push_back(street);

    this->gv->addEdge((int) street->getEdgeID(),
                      (int) street->getSource()->getID(),
                      (int) street->getDest()->getID(),
                      static_cast<int> (street->getType()));
//    if(!name.empty()){
//        this->gv->setEdgeLabel((int) street->getEdgeID(), street->getName());
//    }
//    this->gv->setEdgeWeight((int) street->getEdgeID(), (int) weight);
//    this->gv->setEdgeColor((int) street->getEdgeID(), BLACK);
}

void GarbageManagement::addVehicle(unsigned long garageID, Vehicle *vehicle) {
    Garage *garage= this->getGarage(garageID);
    if(garage != nullptr){
        garage->addVehicle(vehicle);
    }
    else{
        std::cout << "Error: Couldn't find Garage." << std::endl;
    }
}

void GarbageManagement::addVehicle(Vehicle *vehicle){
    this->gv->addNode((int) vehicle->getPlace()->getID(),
                      vehicle->getPlace()->getCoordinates().first,
                      vehicle->getPlace()->getCoordinates().second);
    this->gv->setVertexIcon((int) vehicle->getPlace()->getID(), vehicleImgPath);
}

void GarbageManagement::removePlace(Place* place){
    auto it = std::find(this->places.begin(), this->places.end(), place);
    if (it != this->places.end()) {
        this->places.erase(it);
    }
}

void GarbageManagement::removeEmptyPlace(const unsigned long &ID) {
    Place *p = getEmptyPlace(ID);

    //remove from graph
    if(!this->graph.removeNode((*p))){
        std::cout << "Node " << p->getID() << " not in graph." << std::endl;
        return;
    }

    removePlace(p);

    this->gv->removeNode((int) p->getID());
}

void GarbageManagement::removeStation(const unsigned long &stationID) {
    Station *s = getStation(stationID);

    //remove from graph
    if(!this->graph.removeNode((*s->getPlace()))){
        std::cout << "Node " << s->getPlace()->getID() << " not in graph." << std::endl;
        return;
    }

    removePlace(s->getPlace());

    auto it = std::find(this->stations.begin(), this->stations.end(), s);
    if (it != this->stations.end()) {
        this->stations.erase(it);
    }

    this->gv->removeNode((int) s->getPlace()->getID());
}

void GarbageManagement::removeContainer(const unsigned long &containerID) {
    Container *c = getContainer(containerID);

    //remove from graph
    if(!this->graph.removeNode((*c->getPlace()))){
        std::cout << "Node " << c->getPlace()->getID() << " not in graph." << std::endl;
        return;
    }

    removePlace(c->getPlace());

    auto it = std::find(this->containers.begin(), this->containers.end(), c);
    if (it != this->containers.end()) {
        this->containers.erase(it);
    }

    this->gv->removeNode((int) c->getPlace()->getID());
}

void GarbageManagement::removeGarage(const unsigned long &garageID) {
    Garage *g = getGarage(garageID);

    //remove from graph
    if(!this->graph.removeNode((*g->getPlace()))){
        std::cout << "Node " << g->getPlace()->getID() << " not in graph." << std::endl;
        return;
    }

    removePlace(g->getPlace());

    auto it = std::find(this->garages.begin(), this->garages.end(), g);
    if (it != this->garages.end()) {
        this->garages.erase(it);
    }

    this->gv->removeNode((int) garageID);
}

void GarbageManagement::removeVehicle(Vehicle *vehicle){
    this->gv->removeNode((int) vehicle->getPlace()->getID());
}

void GarbageManagement::removeEdge(const unsigned long &ID) {
    Street *s = getStreet(ID);

    if(s == nullptr){
        std::cout << "Edge " << ID << " not in graph." << std::endl;
        return;
    }

    while(s != nullptr){
        Place* source = s->getSource();
        Place* dest = s->getDest();

        this->graph.removeEdge(*source, *dest);

        this->gv->removeEdge(s->getEdgeID());

        auto it = std::find(this->streets.begin(), this->streets.end(), s);
        if (it != this->streets.end()) {
            this->streets.erase(it);
        }

        s = getStreet(ID);
    }
}

void GarbageManagement::resetVehicles() {
    for(auto g: garages){
        for(auto v: g->getVehicles()){
            v->reset();
        }
    }
}

void GarbageManagement::evalCon() {

}

void GarbageManagement::collectGarbage() {
    if(stations.empty() || containers.empty() || garages.empty()){
        std::cout << "No stations, containers or garages." << std::endl;
        return;
    }

    resetVehicles(); //only needed sometimes, so let's keep it out of the timer

    clock_t tBegin = clock();

    if(algorithm==Algorithm::Warshall){
        graph.floydWarshall();
    }

    //get filled containers
    std::vector<Container *> filledContainers;
    for (auto c: containers){
        if(c->getFilledPer() >= fillPerNeeded){
            filledContainers.push_back(c);
        }
    }

    std::vector<Vehicle *> emptyVehicles = getAllVehicles();

    while(!filledContainers.empty() && !emptyVehicles.empty()){
        std::vector<Place *> path;

        ulong_dist dist(0, emptyVehicles.size()-1);
        unsigned  long vehicleIndex = dist(rng);
        Vehicle *vehicle = emptyVehicles[vehicleIndex];

        path.push_back(vehicle->getGarage()->getPlace());

        auto availableContainers = getContainersByType(vehicle->getType());

        //move vehicle to closest container
        //load
        //remove filled

        while(true){
            //next container if theres none break
            //move
            //load
            //remove filled
        }

        //mover para station
        //unload
    }

    clock_t tEnd = clock();
    double tElapsed = tEnd - tBegin;

    std::cout << "Elapsed time: " << tElapsed << std::endl;

    //print/return vehicles and paths
}


void GarbageManagement::rearrange() {
    this->gv->rearrange();
}

void GarbageManagement::closeWindow() {
    if(gv != nullptr){
        gv->closeWindow();
    }
}

std::vector<std::pair<unsigned long, std::string>> GarbageManagement::getAllStreetNames() {

    std::vector<pair<unsigned long, std:: string>> streetNames;

    bool alreadyExists = false;

    for(auto street: this->getStreets()) {

        alreadyExists = false;

        for(auto existingStreet : streetNames) {
            if(existingStreet.second.compare(street->getName()) == 0) {
                alreadyExists = true;
            }
        }

        if(!alreadyExists && !street->getName().empty()) {
            streetNames.push_back(std::make_pair(street->getID(), street->getName()));
        }
    }

    return streetNames;
}
