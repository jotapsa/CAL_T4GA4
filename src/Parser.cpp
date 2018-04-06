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

bool readLine(fstream& file, vector<std::string> *lineVector){
    string line;

    lineVector->clear();

    if(!getline(file,line,'\n')){
        return false;
    }

    *lineVector = split(line, ';');
    return true;
}

 void setPlace(vector<std::string> line, unsigned long *id, std::pair<double, double> *coordinates) {
     double dLon, dLat, rLon, rLat;

     *id = stoul(line.at(0));

     rLat = stod(line.at(3));
     rLon = stod(line.at(4));

     convertToKilometers(coordinates, rLat, rLon);
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

        setPlace(lineVector, &placeID, &coordinates);
        management.addPlace(new Place(placeID, coordinates));
    }

    places.close();

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
        if(lineVector.size() != 6){
            return false;
        }

        setPlace(lineVector, &placeID, &coordinates);
        management.addContainer(new Container(placeID, coordinates,
                                              getGarbageType(lineVector.at(5)),0));
    }

    containers.close();
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
        if(lineVector.size() != 6){
            return false;
        }

        setPlace(lineVector, &placeID, &coordinates);
        management.addStation(new Station(placeID, coordinates,
                                          getGarbageType(lineVector.at(5)),0));
    }

    stations.close();
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

        for(Vehicle_T v : vehiclesVector){
            if(v.ID == newVehicle.ID || v.plate.compare(newVehicle.plate)==0){
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
    pair <double,double> coordinates;

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

        setPlace(lineVector, &placeID, &coordinates);

        management.addGarage(new Garage(placeID, coordinates));

        if((lineVector.size()-5) <= 0){
            continue;
        }

        for(int i=5; i < lineVector.size(); i++){
            Vehicle *v = getVehicle(stoul(lineVector.at(i)));
            if(v != nullptr){
                management.addVehicle(placeID, v);
            }
        }

           if((lineVector.size()-5) != management.getVehicles(placeID).size()){
            cout << "Couldn't find all vehicles of Garage -> " << placeID << "." << endl;
            return false;
        };
    }

    garages.close();

    if(!vehiclesVector.empty()){
        cout << "Failed to assign all vehicles." << endl;
        return false;
    }

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

    std::cout << edgesVector.size() << "/" << nEdges << " edges were successfully read!\n";
    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream edgesInfo;
    unsigned long int id=0, nEdgesInfo=0, nLines=0;
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

        id = stoul(lineVector.at(0));

        nEdgesInfo++;
        for(Edge_T edge : edgesVector){
            if(edge.ID == id){
                pair <unsigned long int,unsigned long int> nodes
                        = make_pair(edge.node1,edge.node2);
                name = lineVector.at(1);
                type = lineVector.at(2) == "True" ? twoWay : oneWay;

                management.addEdge(0,nodes,type, name);
            }
        }
    }

    edgesInfo.close();

    std::cout << nLines << "/" << nEdgesInfo << " edges info were successfully read!\n\n";
    return true;
}

void savePlaces(const GarbageManagement &management) {
//    for(Place *place : management.getGraph()){
//
//    }
}

void saveContainers(GarbageManagement &management){
//    ofstream containers;
//
//    containers.open("../resources/container.txt");
//
//    if(!containers.is_open()) {
//        cout << "container.txt could not be open!\n";
//        return;
//    }
//    for(Container *container : management.getContainers()){
//        containers << container->getID() << ";" << container->getCapacity();
//    }
}

void saveStations(GarbageManagement &management){
//    ofstream stations;

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
    for(Garage *garage : management.getGarages()){
        saveVehicles(management.getVehicles(garage->getID()));
    }
}

void saveEdges(const GarbageManagement &management) {

}

void saveEdgesInfo(const GarbageManagement &management) {

}
