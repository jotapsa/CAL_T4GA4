#include "Parser.h"
#include "Aux.h"
#include <sstream>
#include <cstdlib>

using namespace std;

struct Edge_T {
    unsigned long int ID;
    std::string name;
    EdgeType type;
};

struct Vehicle_T {
    unsigned long int ID;
    std::string plate;
    std::vector<GarbageType> types;
    std::vector<double> capacities;
};

std::vector<Edge_T> edgesVector;
std::vector<Vehicle_T> vehiclesVector;

bool openFile(fstream& file, std::string filePath){
    file.open(filePath);

    std::cout << "--------------------------------------" << endl;

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open!\n";
        return false;
    }

    std::cout << "Reading file: " << filePath << endl;
    return true;
}

bool openFile(ofstream& file, std::string filePath){
    file.open(filePath);

    std::cout << "--------------------------------------" << endl;

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open!\n";
        return false;
    }

    std::cout << "Saving file: " << filePath << endl;
    return true;
}

std::vector<std::string> split(const std::string &s, const char &delim){
    std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);

    std::string partX;

    while(getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }

    return splitStrings;
}

bool readLine(fstream &file, vector<std::string> *lineVector){
    string line;

    lineVector->clear();

    if(!getline(file,line,'\n')){
        return false;
    }

    *lineVector = split(line, ';');
    return true;
}

Place* newPlace(vector<std::string> line) {
    return new Place(stoul(line.at(0)),
                     stold(line.at(1)),
                     stold(line.at(2)),
                     stold(line.at(3)),
                     stold(line.at(4)),
                     convertToCoords(stold(line.at(1)), stold(line.at(2)),
                                     stold(line.at(3)), stold(line.at(4))));
}

Edge_T createEdge(vector<std::string> line){
    Edge_T edge;

    edge.ID = stoul(line.at(0));
    edge.name = line.at(1);
    edge.type = (line.at(2).compare(std::string("True")) == 0) ? EdgeType:: twoWay : EdgeType:: oneWay;

    return edge;
}

Vehicle_T createVehicle(vector<std::string> line){
    Vehicle_T vehicle;

    vehicle.ID = stoul(line.at(0));
    vehicle.plate = line.at(1);
    //TODO iterator
    for(int i=2; i < line.size(); i+=2){
        vehicle.types.push_back(getGarbageType(line.at(i)));
        vehicle.capacities.push_back(stod(line.at(i+1)));
    }

    return vehicle;
}

Vehicle* getVehicle(unsigned long int vehicleID, Garage *garage){
    Vehicle *vehicle;

    if(vehiclesVector.empty()){
        return nullptr;
    }

    vector<Vehicle_T>::iterator v = vehiclesVector.begin();

    while(v != vehiclesVector.end()){
        if(v->ID == vehicleID){
            vehicle = new Vehicle(v->ID, garage,v->plate, v->types, v->capacities);
            vehiclesVector.erase(v);
            return vehicle;
        }
        v++;
    }

    return nullptr;
}

bool loadPlaces(GarbageManagement &management) {
    fstream places;
    unsigned long nPlaces=0;
    vector<std::string> lineVector;

    if(!openFile(places, PLACES_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(places, &lineVector)){
        nPlaces++;
        if(lineVector.size() < 5){
            return false;
        }

        management.addPlace(newPlace(lineVector));
    }

    places.close();

    management.rearrange();
    std::cout << management.getGraph().getNumNodes() << "/" << nPlaces << " places were successfully read!\n";
    return true;
}

bool loadContainers(GarbageManagement &management){
    fstream containers;
    unsigned int nContainers=0;
    vector<std::string> lineVector;

    if(!openFile(containers, CONTAINERS_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(containers, &lineVector)){
        nContainers++;
        if(lineVector.size() != 7){
            return false;
        }

        management.addContainer(new Container(newPlace(lineVector), getGarbageType(lineVector.at(5)), stod(lineVector.at(6))));
    }

    containers.close();

    management.rearrange();
    std::cout << management.getContainers().size() << "/" << nContainers << " containers were successfully read!\n";
    return true;
}

bool loadStations(GarbageManagement &management){
    fstream stations;
    unsigned int nStations=0;
    vector<std::string> lineVector;

    if(!openFile(stations, STATIONS_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(stations, &lineVector)){
        nStations++;
        if(lineVector.size() != 5){
            return false;
        }

        management.addStation(new Station(newPlace(lineVector)));
    }

    stations.close();

    management.rearrange();
    std::cout << management.getStations().size() << "/" << nStations << " stations were successfully read!\n";
    return true;
}

bool loadVehicles(GarbageManagement &management){
    fstream vehicles;
    unsigned long int nVehicles=0;
    vector<std::string> lineVector;

    if(!openFile(vehicles, VEHICLES_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(vehicles, &lineVector)) {
        nVehicles++;

        if(lineVector.size() < 4 || (lineVector.size()-2)%2 != 0){
            return false;
        }

        Vehicle_T newVehicle = createVehicle(lineVector);

        for(vector<Vehicle_T>::iterator v = vehiclesVector.begin(); v != vehiclesVector.end(); v++){
            if(v->ID == newVehicle.ID || v->plate.compare(newVehicle.plate)==0){
                cout << "Vehicle " << newVehicle.ID << " already exists." << endl;
                return false;
            }
        }

        vehiclesVector.push_back(newVehicle);
    }

    vehicles.close();

    std::cout << vehiclesVector.size() << "/" << nVehicles << " vehicles were successfully read!\n";
    return true;
}

bool loadGarages(GarbageManagement &management){
    fstream garages;
    unsigned long int nGarages=0;
    vector<std::string> lineVector;

    unsigned long placeID;

    if(!openFile(garages, GARAGES_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(garages, &lineVector)){
        nGarages++;
        if(lineVector.size() < 5){
            return false;
        }

        placeID = stoul(lineVector.at(0));
        Garage *g = new Garage(newPlace(lineVector));
        management.addGarage(g);

        if((lineVector.size()-5) <= 0){
            continue;
        }

        for(std::vector<string>::iterator vID = lineVector.begin()+5; vID != lineVector.end(); vID++){
            Vehicle *v = getVehicle(stoul(*vID), g);
            if(v != nullptr){
                management.addVehicle(placeID, v);
            }
        }

       if((lineVector.size()-5) != management.getVehiclesFromGarage(placeID).size()){
            cout << "Couldn't find all vehicles of Garage -> " << placeID << "." << endl;
            return false;
        }
    }

    garages.close();

    if(!vehiclesVector.empty()){
        cout << "Failed to assign all vehicles." << endl;
        return false;
    }

    management.rearrange();
    std::cout << management.getGarages().size() << "/" << nGarages << " garages were successfully read!\n";
    return true;
}

bool loadEdges(GarbageManagement &management) {
    fstream edges;
    unsigned long int nEdges=0, ID, node1, node2;
    vector<std::string> lineVector;

    if(!openFile(edges, EDGES_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(edges, &lineVector)){
        nEdges++;
        if(lineVector.size() != 3){
            return false;
        }

        ID = stoul(lineVector.at(0));
        node1 = stoul(lineVector.at(1));
        node2 = stoul(lineVector.at(2));

        for(std::vector<Edge_T>::iterator edge = edgesVector.begin(); edge != edgesVector.end(); edge++){
            if(edge->ID == ID){
                pair <unsigned long int,unsigned long int> nodes = make_pair(node1,node2);
                management.addEdge(0, edge->ID, nodes, edge->type, edge->name);
                break;
            }
        }

    }

    edges.close();

    management.rearrange();
    std::cout << management.getStreets().size() << "/" << nEdges << " edges were successfully read!\n\n";
    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream edgesInfo;
    unsigned long int nEdgesInfo=0;
    vector<std::string> lineVector;

    if(!openFile(edgesInfo, EDGES_INFO_FILEPATH(management.getMapPath()))){
        return false;
    }

    while(readLine(edgesInfo, &lineVector)){
        nEdgesInfo++;
        if(lineVector.size() != 3){
            return false;
        }

        edgesVector.push_back(createEdge(lineVector));
    }

    edgesInfo.close();

    std::cout << edgesVector.size() << "/" << nEdgesInfo << " edgesInfo were successfully read!\n";
    return true;
}

bool saveMap(const GarbageManagement &management){
    fstream mapList(MAPSLIST_FILEPATH, ios::in | ios::out | ios::app);
    std::string line;
    const char* createMap;

    while(getline(mapList, line)){
        if (line.find(management.getMapName()) != std::string::npos) {
            return false;
        }
    }

    mapList.clear() ;

    createMap = std::string(CREATE_MAP_PATH(management.getMapPath())).c_str();
    if(system(createMap) == -1){
        std::cout << management.getMapName() << "couldn't be saved.\n\n";
        return false;
    }

    mapList << management.getMapName() << ";" << management.getMapPath() << endl;

    mapList.close();
    return true;
}

void savePlaces(const GarbageManagement &management){
    ofstream places;

    if(!openFile(places,PLACES_FILEPATH(management.getMapPath()))){
        return;
    }

    for(auto place : management.getEmptyPlaces()){
        places << place->toString() << endl;
    }

    places.close();
}

void saveContainers(const GarbageManagement &management){
    ofstream containers;

    if(!openFile(containers,CONTAINERS_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Container *container : management.getContainers()){
        containers << container->toString() << endl;
    }

    containers.close();
}

void saveStations(const GarbageManagement &management){
    ofstream stations;

    if(!openFile(stations,STATIONS_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Station *station : management.getStations()){
        stations << station->toString() << endl;
    }

    stations.close();
}

void saveVehicles(const GarbageManagement &management){
    ofstream vehicles;

    if(!openFile(vehicles,VEHICLES_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Vehicle *v : management.getVehicles()){
        vehicles << v->toString() << endl;
    }

    vehicles.close();
}

void saveGarages(const GarbageManagement &management){
    ofstream garages;

    if(!openFile(garages,GARAGES_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Garage *garage : management.getGarages()){
        garages << garage->toString() << endl;
    }

    garages.close();
}

void saveEdges(const GarbageManagement &management) {
    ofstream edges;

    if(!openFile(edges,EDGES_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Street *street : management.getStreets()){
        edges << street->toString() << endl;
    }

    edges.close();
}

void saveEdgesInfo(const GarbageManagement &management) {
    ofstream edgesInfo;
    unsigned long int actualID=0;

    if(!openFile(edgesInfo,EDGES_INFO_FILEPATH(management.getMapPath()))){
        return;
    }

    for(Street *street : management.getStreets()){
        if(street->getID() == actualID){
            continue;
        }
        actualID = street->getID();
        edgesInfo << street->getInfo() << endl;
    }

    edgesInfo.close();
}