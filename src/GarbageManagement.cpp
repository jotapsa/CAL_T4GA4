#include "GarbageManagement.h"
#include "Aux.h"
#include "Cli.h"
#include "kmpMatcher.h"
#include "editDistance.h"
#include <sstream>
#include "Parser.h"

GarbageManagement::GarbageManagement() {
    this->algorithm = static_cast<Algorithm>(DEFAULT_ALGORITHM);
    this->fillPerNeeded = DEFAULT_FILL_PER_NEEDED;
}

void GarbageManagement::initGraphViewer(){
    gv = new GraphViewer(windowWidth, windowHeight, false);

    if(getImageSize(backgroundImgPath(this->mapPath), &this->imageWidth, &this->imageHeight)){
        gv->setBackground(backgroundImgPath(this->mapPath));
    }
    else{
        this->imageWidth = 1920;
        this->imageHeight = 1080;
    }

    gv->createWindow(windowWidth, windowHeight);
    gv->defineEdgeCurved(curvedEdges);
    gv->defineVertexSize(emptyPlaceNodeSize);
    gv->defineVertexColor(BLUE);

    updateMapCoords(this->getCoords(), this->imageWidth, this->imageHeight);
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


std::vector<Station *> GarbageManagement::getStations() const{
    return this->stations;
}

std::vector<Garage *> GarbageManagement::getGarages() const{
    return this->garages;
}

std::vector<Street *> GarbageManagement::getStreets() const{
    return this->streets;
}

std::vector<Vehicle *> GarbageManagement::getVehicles() const {
    return this->vehicles;
}

std::vector<Vehicle *> GarbageManagement::getVehiclesFromGarage(unsigned long garageID) const{
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

Street *GarbageManagement::getStreet(unsigned long ID) const {
    for(auto s: streets){
        if(s->getID() == ID){
            return s;
        }
    }
    return nullptr;
}

Street *GarbageManagement::getStreet(Place *p1, Place *p2) const {
    for(auto s: streets){
        if( (s->getSource()->getID() == p1->getID()) && (s->getDest()->getID() == p2->getID()) ){
            return s;
        }
    }

    return nullptr;
}

Vehicle *GarbageManagement::getVehicle(unsigned long vehicleID) const {
    for(auto v: vehicles){
        if(v->getID() == vehicleID){
            return v;
        }
    }
    return nullptr;
}

std::string GarbageManagement::getMapPath() const {
    return this->mapPath;
}

std::string GarbageManagement::getMapName() const {
    return this->mapName;
}

std::vector<double> GarbageManagement::getCoords() const {
    std::vector<double> coords;

    coords.push_back(this->minLat);
    coords.push_back(this->minLon);
    coords.push_back(this->maxLat);
    coords.push_back(this->maxLon);

    return coords;
}

std::vector<Container *>
GarbageManagement::getMatchingContainers(Vehicle *vehicle, std::vector<Container *> containers, bool differentiated) {
    std::vector<Container *> containersMatch;

    for(Container *c : containers){
        if(differentiated){
            if(vehicle->hasType(c->getType())){
                if(vehicle->getFreeSpaceForType(c->getType()) >= (c->getFilled())){
                    containersMatch.push_back(c);
                }
            }
        }
        else{
            if(vehicle->getTotalFreeSpace() >= (c->getFilled())){
                containersMatch.push_back(c);
            }
        }
    }

    return containersMatch;
}

Container * GarbageManagement::getClosestContainerToVehicle(Vehicle *vehicle, std::vector<Container *> containers,
                                                            bool differentiated) {
    std::vector<Container *> matchingContainers = getMatchingContainers(vehicle, containers, differentiated);
    std::vector<Place> matchingPlaces;
    for(auto c: matchingContainers){
        matchingPlaces.push_back(*(c->getPlace()));
    }

    if(algorithm==Algorithm::Dijkstra){
        graph.dijkstra(*(vehicle->getPlace()));
    }else if(algorithm == Algorithm::Warshall){
        //pre proc already done
    }

    Place *place;
    if(algorithm == Algorithm::Dijkstra){
        place = graph.getNodeWithShortestPathDijkstra(matchingPlaces);
    }else if(algorithm == Algorithm::Warshall){
        place = graph.getNodeWithShortestPathFloydWarshall(*(vehicle->getPlace()), matchingPlaces);
    }

    if(place == nullptr){
        return nullptr;
    }

    for (auto &matchingContainer : matchingContainers) {
        if(*(matchingContainer->getPlace()) == *(place)){
            return matchingContainer;
        }
    }

    return nullptr;
}

Station *GarbageManagement::getClosestStationToVehicle(Vehicle *vehicle, std::vector<Station *> stations) {
    std::vector<Place> places;
    for(auto s: stations){
        places.push_back(*(s->getPlace()));
    }

    if(algorithm==Algorithm::Dijkstra){
        graph.dijkstra(*(vehicle->getPlace()));
    }else if(algorithm == Algorithm::Warshall){
        //pre proc already done
    }

    Place *place;
    if(algorithm==Algorithm::Dijkstra){
        place = graph.getNodeWithShortestPathDijkstra(places);
    }else if(algorithm == Algorithm::Warshall){
        place = graph.getNodeWithShortestPathFloydWarshall(*(vehicle->getPlace()), places);
    }

    if(place == nullptr){
        return nullptr;
    }

    for (auto &station : stations) {
        if(*(station->getPlace()) == *(place)){
            return station;
        }
    }

    return nullptr;
}

void GarbageManagement::setCoords(double minLat, double minLon, double maxLat, double maxLon){
    this->minLat = minLat;
    this->minLon = minLon;
    this->maxLat = maxLat;
    this->maxLon = maxLon;
}

void GarbageManagement::setMapPath(std::string mapPath){
    this->mapPath = std::move(mapPath);
}

void GarbageManagement::setMapName(std::string mapName){
    this->mapName = std::move(mapName);
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

    if(sourceNode == nullptr){
        std::cout << "Couldn't find place: " << nodeIDs.first << std::endl;
        return;
    }

    if(destNode == nullptr){
        std::cout << "Couldn't find place: " << nodeIDs.second << std::endl;
        return;
    }

    if(weight == 0){
        weight = getDistance(sourceNode->getLat(), sourceNode->getLon(),
                             destNode->getLat(), destNode->getLon());
    }

    if(!this->graph.addEdge(*(sourceNode), *(destNode), weight, type)){
        std::cout << "Error: Cannot add edge." << std::endl;
        return;
    }

    Street *street = new Street(ID, sourceNode, destNode, std::move(name), type);
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
        this->vehicles.push_back(vehicle);
    }
    else{
        std::cout << "Error: Couldn't find Garage." << std::endl;
    }
}

void GarbageManagement::addVehicleToGraph(Vehicle *vehicle){
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

void GarbageManagement::removeVehicle(const unsigned long &vehicleID) {
    Vehicle *v = getVehicle(vehicleID);
    Garage *g = v->getGarage();

    auto it = std::find(this->vehicles.begin(), this->vehicles.end(), v);
    if (it != this->vehicles.end()) {
        g->removeVehicle(vehicleID);
        this->vehicles.erase(it);
    }
}

void GarbageManagement::removeVehicleFromGraph(Vehicle *vehicle) {
    this->gv->clearVertexIcon((int) vehicle->getPlace()->getID());
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

void GarbageManagement::resetContainers() {
    for(auto c: containers){
        c->reset();
    }
}

void GarbageManagement::resetVehicles() {
    for(auto v: vehicles){
        v->reset();
    }
}


void GarbageManagement::evalCon() {
    auto places = getPlaces();
    if(places.empty()){
        std::cout << "No places." << std::endl;
        return;
    }

    if(!this->graph.isDAG()){
        std::cout << "This graph is not Directed acyclic." << std::endl;
    } else{
        std::cout << "This graph is Directed acyclic." << std::endl;
    }


    graph.resetNodeAuxFields();
    std::vector<Place> visitOrder = graph.dfs();

    Graph<Place> cloneGraph = this->graph.clone();
    cloneGraph.invertEdges();
    cloneGraph.resetNodeAuxFields();

    std::cout << "Following are strongly connected components in graph." << std::endl;
    for(auto p: visitOrder){
        if(!cloneGraph.getNodeVisited(p)){
            std::vector<Place> scc;
            cloneGraph.dfsVisit(cloneGraph.getNode(p), scc);
            for(auto c: scc){
                std::cout << c.getID() << " ";
            }
            std::cout << std::endl;
        }
    }

    bool stronglyCon = true;

    std::vector<Node<Place> *> nodeSet = graph.getNodeSet();
    for(auto n: nodeSet){
        graph.resetNodeAuxFields();
        std::vector<Place> visitedNodes;
        graph.dfsVisit(n, visitedNodes);

        if(visitedNodes.size() != graph.getNumNodes()){
            stronglyCon = false;

            std::cout << "Number of visited nodes performing dfs from this node: " << visitedNodes.size() << std::endl;
            std::cout << "Number of nodes in the graph: " << graph.getNumNodes() << std::endl;
            std::cout << "Node nº: " << n->getInfo().getID() << " is not strongly connected to the graph." << std::endl;
        }
    }

    if(stronglyCon){
        std::cout << "Graph is strongly connected ." << std::endl;
        std::cout << "There is a directed path from x to y and a directed path from y to x for every pair of vertices {x, y}. " << std::endl;
    } else{
        std::cout << "Graph is not strongly connected ." << std::endl;
        std::cout << "There is not a directed path from x to y and a directed path from y to x for every pair of vertices {x, y}. " << std::endl;
    }
}

void GarbageManagement::collectGarbage(bool differentiated) {
    if(stations.empty() || containers.empty() || garages.empty()){
        std::cout << "No stations, containers or garages." << std::endl;
        return;
    }

    //only needed sometimes, so let's keep it out of the timer
    resetVehicles();
    resetContainers();
    graph.resetNodeAuxFields();

    clock_t tBegin = clock();

    if(algorithm == Algorithm::Dijkstra){
        //No need for pre-processing (yet)
    }else if(algorithm == Algorithm::Warshall){
        graph.floydWarshall();
    }

    //get filled containers with cloned values
    std::vector<Container *> filledContainers;
    for (auto c: containers){
        if(c->getFilledPer() >= fillPerNeeded){
            filledContainers.push_back(c);
        }
    }

    //clone
    std::vector<Vehicle *> emptyVehicles;
    for(auto v: vehicles){
        if(!v->getFull()){
            emptyVehicles.push_back(v);
        }
    }

    std::vector<Vehicle *> trucks;
    std::vector<std::vector<Place *>> paths;

    while(!filledContainers.empty() && !emptyVehicles.empty()){
        std::vector<Place *> path;

        //chose vehicle randomly
        ulong_dist dist(0, emptyVehicles.size()-1);
        unsigned long vehicleIndex = dist(rng);
        Vehicle *vehicle = emptyVehicles[vehicleIndex];

        auto vehicle_it = std::find(emptyVehicles.begin(), emptyVehicles.end(), vehicle);
        if (vehicle_it != emptyVehicles.end()) {
            emptyVehicles.erase(vehicle_it);
        }

        Container *container = getClosestContainerToVehicle(vehicle, filledContainers, differentiated);
        //No container that the vehicle is able to "load"
        if(container == nullptr){
            continue;
        }

        //move vehicle to closest container
        std::vector<Place *> intermediatePath;
        if(algorithm == Algorithm::Dijkstra){
            intermediatePath = graph.getDijkstraPath(*(container->getPlace()));
        }else if(algorithm == Algorithm::Warshall){
            graph.getfloydWarshallPath(intermediatePath, *(vehicle->getPlace()), *(container->getPlace()));
        }

        vehicle->moveTo(container->getPlace());
        vehicle->loadFromContainer(container, differentiated);

        //remove from filledContainers
        auto container_it = std::find(filledContainers.begin(), filledContainers.end(), container);
        if (container_it != filledContainers.end()) {
            filledContainers.erase(container_it);
        }

        while((container = getClosestContainerToVehicle(vehicle, filledContainers, differentiated)) != nullptr){
            if(algorithm == Algorithm::Warshall){
                graph.getfloydWarshallPath(intermediatePath, *(vehicle->getPlace()), *(container->getPlace()));
            }else if(algorithm == Algorithm::Dijkstra){
                intermediatePath = graph.getDijkstraPath(*(container->getPlace()));
            }
            for(auto p: intermediatePath){
                path.push_back(p);
            }

            vehicle->moveTo(container->getPlace());
            vehicle->loadFromContainer(container, differentiated);

            //remove from filledContainers
            container_it = std::find(filledContainers.begin(), filledContainers.end(), container);
            if (container_it != filledContainers.end()) {
                filledContainers.erase(container_it);
            }
        }
        vehicle->setFull(true);

        std::vector<Station *> cloneStations(this->stations);
        Station *station = getClosestStationToVehicle(vehicle, cloneStations);

        if(station == nullptr){
            continue;
        }

        if(algorithm==Algorithm::Warshall){
            graph.getfloydWarshallPath(intermediatePath, *(vehicle->getPlace()), *(station->getPlace()));
        }else if(algorithm == Algorithm::Dijkstra){
            intermediatePath = graph.getDijkstraPath(*(station->getPlace()));
        }
        for(auto p: intermediatePath){
            path.push_back(p);
        }

        vehicle->moveTo(station->getPlace());
        vehicle->unloadToStation(station);

        trucks.push_back(vehicle);
        paths.push_back(path);
    }

    clock_t tEnd = clock();
    double tElapsed = tEnd - tBegin;

    std::cout << "Elapsed time: " << tElapsed << std::endl << std::endl;

    feedback(trucks, paths);
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

    std::vector<std::pair<unsigned long, std:: string>> streetNames;

    bool alreadyExists = false;

    for(auto street: this->getStreets()) {

        alreadyExists = false;

        for(auto existingStreet : streetNames) {
            if(existingStreet.second == street->getName()) {
                alreadyExists = true;
            }
        }

        if(!alreadyExists && !street->getName().empty()) {
            streetNames.emplace_back(street->getID(), street->getName());
        }
    }

    return streetNames;
}

void GarbageManagement::printResults(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths) {
    for(unsigned long i=0; i<vehicles.size(); i++){
        std::cout << "--------- " << vehicles.at(i)->getPlate() << " ---------" << std::endl;

        unsigned long noStop = 1;
        for(auto p: paths.at(i)){
            std::cout << noStop++ <<"nth stop was : " << p->getID() << std::endl;
        }
    }

}

void GarbageManagement::resetStreetsGraph(){
    for(auto s : streets){
        this->gv->setEdgeColor((int) s->getEdgeID(), BLACK);
        this->gv->setEdgeThickness((int) s->getEdgeID(), 1);
    }
}

void GarbageManagement::updateBuildingsGraph(){

    for(Container *container : this->containers){
        this->gv->setVertexIcon((int) container->getPlace()->getID(), getGarbageTypeImgPath(container->getType()));
    }

    for(Station *station : this->stations){
        this->gv->setVertexIcon((int) station->getPlace()->getID(), stationImgPath);
    }

    for(Garage *garage : this->garages){
        this->gv->setVertexIcon((int) garage->getPlace()->getID(), garageImgPath);
    }
}

bool GarbageManagement::updateVehicle(Vehicle * vehicle, std::vector<Place *> path, std::vector<Street *> streetsVehicle, unsigned int *index){
    if(*index >= path.size()){
        return false;
    }

    if(*index>0){
        removeVehicleFromGraph(vehicle);
    }

    Place *place = path.at(*index);

    vehicle->moveTo(place);
    addVehicleToGraph(vehicle);

    (*index)++;
    return true;
}

void GarbageManagement::visualFeedback(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths) {
    std::vector<std::vector<Street *>> streets;
    unsigned int index[vehicles.size()];
    bool display=true;

    for(unsigned int v=0; v < vehicles.size(); v++){
        index[v] = 0;

        std::vector<Street *> pathVehicle;
        streets.push_back(pathVehicle);

        if(paths.at(v).empty()){
            continue;
        }

        for(unsigned int p=0; p < paths.at(v).size()-1; p++){
            Street* street = getStreet(paths.at(v).at(p), paths.at(v).at(p+1));
            if(street != nullptr){
                streets.at(v).push_back(street);
                this->gv->setEdgeColor((int) street->getEdgeID(), RED);
                this->gv->setEdgeThickness((int) street->getEdgeID(), 2);
            }
            else{
//                std::cout << "STREET NOT FOUND!" << std::endl;
//                return;
            }
        }

//        std::cout << "Vehicle " << vehicles.at(v)->getID() << " -> " << streets.at(v).size() << "/" << paths.at(v).size() << " streets found." << std::endl;
    }

    while(display){
        updateBuildingsGraph();
        display=false;
        for(int v=0; v < vehicles.size(); v++){
           display |= updateVehicle(vehicles.at(v), paths.at(v), streets.at(v) ,&index[v]);
        }
        rearrange();
        usleep(100000);
    }

    resetStreetsGraph();
    rearrange();
}

void GarbageManagement::feedback(std::vector<Vehicle *> vehicles, std::vector<std::vector<Place *>> paths) {
    printResults(vehicles, paths);
    std::cout << "\nDo you wish to get visual feedback?" << std::endl;
    if(readConfirmation()){
        visualFeedback(vehicles, paths);
    }
}

std::vector<Street *> GarbageManagement::getStreetByName(std::string streetName, bool kmp){
    std::vector<Street *> streetsMatch;

    for(Street *s : this->streets){
        if(kmp && kmpMatcher::matches(s->getName(), streetName)){
            streetsMatch.push_back(s);
        }
        else if(s->getName() == streetName){
            streetsMatch.push_back(s);
        }
    }

    return streetsMatch;
}

std::vector<std::pair<Container*, std::string>> GarbageManagement::getStreetContainers(std::vector<Street *> edges){
    std::vector<std::pair<Container*, std::string>> containersStreet;

    for(int i = 0; i < edges.size(); i++){
        Street* s = edges.at(i);

        while(i < edges.size() && s->getName() == edges.at(i)->getName()){
            s = edges.at(i);
            if(getContainer(s->getSource()->getID()) != nullptr || getContainer(s->getDest()->getID()) != nullptr){
                Container *c = getContainer(s->getSource()->getID()) != nullptr ?
                                   getContainer(s->getSource()->getID()) :
                                   getContainer(s->getDest()->getID());

                if( std::find(containersStreet.begin(), containersStreet.end(), std::make_pair(c, s->getName())) == containersStreet.end()){
                    containersStreet.push_back(std::make_pair(c, s->getName()));
                }
            }
            i++;
        }
    }
    return containersStreet;
}

Container* GarbageManagement::getContainerStreets(std::string firstStreetName, std::string secondStreetName, bool kmp){
    std::vector<Street *> firstStreet, secondStreet;
    std::vector<std::pair<Container*, std::string>> firstContainers, secondContainers;

    firstStreet = getStreetByName(firstStreetName, kmp);
    secondStreet = getStreetByName(secondStreetName, kmp);

    firstContainers = getStreetContainers(firstStreet);
    secondContainers = getStreetContainers(secondStreet);

    if(firstContainers.size() == 0 || secondContainers.size() == 0){
        return nullptr;
    }

    for(std::pair<Container*, std::string> f : firstContainers){
        for(std::pair<Container*, std::string> s : secondContainers){
            if(f.first->getPlace()->getID() == s.first->getPlace()->getID()){
                std::cout << std::endl << f.second << " <-> " << s.second << " -----> ";
                return f.first;
            }
        }
    }

    return nullptr;
}

std::string GarbageManagement::filterNameStreet(std::string streetName){
    std::vector<std::string> toFilterBegin = {"Rua do ", "Rua de ", "Rua da ", "Rua ","Avenida ", "Alameda ", "Praceta ", "Estrada ", "Travessa do ", "Travessa de ",
                                       "Travessa ", "Praça de ", "Praça da "};
    std::vector<std::string> toFilter = {"das ", "dos ", "da ", "de ", "do ", "e "};

    for(std::string filter : toFilterBegin){
        if(streetName.find(filter) != std::string::npos){
            streetName.erase(0, filter.size());
            break;
        }
    }

    for(std::string filter : toFilter){
        if(streetName.find(filter) != std::string::npos){
            return streetName.replace(streetName.find(filter), filter.size(), "");
        }
    }

    return streetName;
}

bool comp(std::pair<std::string,int> a, std::pair<std::string,int> b) {
    return a.second < b.second;
}

std::vector<std::pair<std::string, int>> GarbageManagement::bestStreets(std::string streetName){
    std::unordered_map<std::string, int> bestStreetsMatch;

    std::vector<std::string> searchStreet;
    searchStreet = split(streetName, ' ');

    for(Street *s : this->streets){
        if(s->getName().size() > 0){
            std::string filtered = filterNameStreet(s->getName());
            std::vector<std::string> cmpStreet = split(filterNameStreet(s->getName()), ' ');

            for(std::string searchStr : searchStreet){
                for(std::string cmpStr : cmpStreet){
                    int distance = editDistance::calculateDistance(cmpStr, searchStr);
                    if(distance < 3){
                        bestStreetsMatch.insert({s->getName(), distance});
                    }
                }
            }
        }
    }

    //Order bestStreetsMatch by Distance
    std::vector<std::pair<std::string, int>> bestStreetsOrder(bestStreetsMatch.begin(), bestStreetsMatch.end());
    std::sort(bestStreetsOrder.begin(), bestStreetsOrder.end(), comp);

//    for(auto& p: bestStreetsOrder)
//        std::cout << p.first << " => " << p.second << '\n';

    return bestStreetsOrder;
}
