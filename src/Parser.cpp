#include "Parser.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include "Aux.h"

using namespace std;

struct Edge_T {
    unsigned long int ID, node1, node2;
};

struct Vehicle_T {
    unsigned long int ID;
    std::string plate;
    GarbageType type;
    double capacity;
};

std::vector<Edge_T> edgesVector;
std::vector<Vehicle_T> vehiclesVector;

bool openFile(fstream& file, std::string filePath){
    file.open(filePath);

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open!\n";
        return false;
    }

    std::cout << "--------------------------------------" << endl;
    std::cout << "Reading file: " << filePath << endl;
    return true;
}

bool openFile(ofstream& file, std::string filePath){
    file.open(filePath);

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open!\n";
        return false;
    }

    std::cout << "--------------------------------------" << endl;
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

Place* newPlace(vector<std::string> line){
    return new Place(stoul(line.at(0)),
                     stod(line.at(1)),
                     stod(line.at(2)),
                     stod(line.at(3)),
                     stod(line.at(4)),
                     convertToCoords(stod(line.at(1)), stod(line.at(2)),
                                     stod(line.at(3)), stod(line.at(4))));
}

Edge_T createEdge(vector<std::string> line){
    Edge_T edge;

    edge.ID = stoul(line.at(0));
    edge.node1 = stoul(line.at(1));
    edge.node2 = stoul(line.at(2));

    return edge;
}

Vehicle_T createVehicle(vector<std::string> line){
    Vehicle_T vehicle;

    vehicle.ID = stoul(line.at(0));
    vehicle.plate = line.at(1);
    vehicle.type = getGarbageType(line.at(2));
    vehicle.capacity = stod(line.at(3));

    return vehicle;
}

Vehicle* getVehicle(unsigned long int vehicleID){
    Vehicle *vehicle;

    if(vehiclesVector.empty()){
        return nullptr;
    }

    vector<Vehicle_T>::iterator v = vehiclesVector.begin();

    while(v != vehiclesVector.end()){
        if(v->ID == vehicleID){
            vehicle = new Vehicle(v->ID,v->plate, v->type, v->capacity);
            vehiclesVector.erase(v);
            return vehicle;
        }
        v++;
    }

    return nullptr;
}

bool loadPlaces(GarbageManagement &management) {
    fstream places;
    unsigned long placeID, nPlaces=0;
    pair <double,double> coordinates;
    vector<std::string> lineVector;

    if(!openFile(places, PLACES_FILEPATH)){
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

    unsigned long placeID;
    pair <double,double> coordinates;

    if(!openFile(containers, CONTAINERS_FILEPATH)){
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

    unsigned long placeID;
    pair <double,double> coordinates;

    if(!openFile(stations, STATIONS_FILEPATH)){
        return false;
    }

    while(readLine(stations, &lineVector)){
        nStations++;
        if(lineVector.size() != 7){
            return false;
        }

        management.addStation(new Station(newPlace(lineVector), getGarbageType(lineVector.at(5)), stod(lineVector.at(6))));
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

    if(!openFile(vehicles, VEHICLES_FILEPATH)){
        return false;
    }

    while(readLine(vehicles, &lineVector)) {
        nVehicles++;

        if(lineVector.size() != 4){
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

    if(!loadVehicles(management)){
        std::cout << "Failed to read vehicles!" << std::endl;
        return false;
    }

    if(!openFile(garages, GARAGES_FILEPATH)){
        return false;
    }

    while(readLine(garages, &lineVector)){
        nGarages++;
        if(lineVector.size() < 5){
            return false;
        }

        management.addGarage(new Garage(newPlace(lineVector)));

        placeID = stoul(lineVector.at(0));

        if((lineVector.size()-5) <= 0){
            continue;
        }

        for(std::vector<string>::iterator vID = lineVector.begin()+5; vID != lineVector.end(); vID++){
            Vehicle *v = getVehicle(stoul(*vID));
            if(v != nullptr){
                management.addVehicle(placeID, v);
            }
        }

       if((lineVector.size()-5) != management.getVehicles(placeID).size()){
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
    unsigned long int nEdges=0;
    vector<std::string> lineVector;

    if(!openFile(edges, EDGES_FILEPATH)){
        return false;
    }

    while(readLine(edges, &lineVector)){
        nEdges++;
        if(lineVector.size() != 3){
            return false;
        }

        edgesVector.push_back(createEdge(lineVector));
    }

    edges.close();

    management.rearrange();
    std::cout << edgesVector.size() << "/" << nEdges << " edges were successfully read!\n";
    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream edgesInfo;
    unsigned long int ID=0, nEdgesInfo=0, nLines=0;
    string name;
    vector<std::string> lineVector;
    EdgeType type;

    if(!openFile(edgesInfo, EDGES_INFO_FILEPATH)){
        return false;
    }

    while(readLine(edgesInfo, &lineVector)){
        nLines++;
        if(lineVector.size() != 3){
            return false;
        }
        nEdgesInfo++;

        ID = stoul(lineVector.at(0));
        name = lineVector.at(1);
        type = (lineVector.at(2).compare(std::string("True")) == 0) ? twoWay : oneWay;

        for(std::vector<Edge_T>::iterator edge = edgesVector.begin(); edge != edgesVector.end(); edge++){
            if(edge->ID == ID){
                pair <unsigned long int,unsigned long int> nodes
                    = make_pair(edge->node1,edge->node2);
//                cout << ID << " - " << lineVector.at(2) << " <-----> ";
                management.addEdge(0, ID, nodes, type, name);
            }
        }
    }

    edgesInfo.close();

    management.rearrange();
    std::cout << nEdgesInfo << "/" << nLines << " edges info were successfully read!\n\n";
    return true;
}

void savePlaces(const GarbageManagement &management) {
    ofstream places;

    if(!openFile(places,PLACES_FILEPATH)){
        return;
    }

    for(auto place : management.getPlaces()){
        places << place->toString() << endl;
    }

    places.close();
}

void saveContainers(GarbageManagement &management){
    ofstream containers;

    if(!openFile(containers,CONTAINERS_FILEPATH)){
        return;
    }

    for(Container *container : management.getContainers()){
        containers << container->toString() << endl;
    }

    containers.close();
}

void saveStations(GarbageManagement &management){
    ofstream stations;

    if(!openFile(stations,STATIONS_FILEPATH)){
        return;
    }

    for(Station *station : management.getStations()){
        stations << station->toString() << endl;
    }

    stations.close();
}

void saveVehicles(std::vector<Vehicle *> vehiclesGarage){
    ofstream vehicles;

    if(!openFile(vehicles,VEHICLES_FILEPATH)){
        return;
    }

    for(Vehicle *v : vehiclesGarage){
        vehicles << v->getID() << ";" << v->getPlate() << ";" << getGarbageType(v->getType()) << ";" << v->getCapacity() << endl;
    }

    vehicles.close();
}

void saveGarages(GarbageManagement &management){
    ofstream garages;

    for(Garage *garage : management.getGarages()){
        saveVehicles(management.getVehicles(garage->getPlace()->getID()));
    }

    if(!openFile(garages,GARAGES_FILEPATH)){
        return;
    }

    for(Garage *garage : management.getGarages()){
        garages << garage->toString() << endl;
    }

    garages.close();
}

void saveEdges(const GarbageManagement &management) {
    ofstream edges;

    if(!openFile(edges,EDGES_FILEPATH)){
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

    if(!openFile(edgesInfo,EDGES_INFO_FILEPATH)){
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
