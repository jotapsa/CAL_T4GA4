#include "Parser.h"
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

struct Edge_T {
    unsigned long int ID, node1, node2;
};

std::vector<Edge_T> edgesVector;
string line;
BuildingType building;
GarbageType type;

bool openFile(fstream& file, std::string filePath){
    file.open(filePath);

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open!\n";
        return false;
    }

    std::cout << "Reading file: " << filePath << endl;
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
    if(!getline(file,line,'\r')){
        return false;
    }

    *lineVector = split(line, ';');
    return true;
}

BuildingType getBuildingType(string type){
    if(type.compare(string("container")) == 0){
        return container;
    }
    else if(type.compare(string("station")) == 0){
        return station;
    }
    else if(type.compare(string("garage")) == 0){
        return garage;
    }
    else{
        return none;
    }
}

GarbageType getGarbageType(string type){
    if(type.compare(string("glass")) == 0){
        return glass;
    }
    else if(type.compare(string("plastic")) == 0){
        return plastic;
    }
    else if(type.compare(string("paper")) == 0){
        return paper;
    }
    else if(type.compare(string("generic")) == 0){
        return generic;
    }
    else{
        return generic;
    }
}

 void setPlace(vector<std::string> line, unsigned long *id, std::pair<double, double> *coordinates){
     double dLon, dLat, rLon, rLat;

     *id = stoul(line.at(0));

     dLat = stod(line.at(1));
     dLon = stod(line.at(2));
     rLat = stod(line.at(3));
     rLon = stod(line.at(4));

     //TODO calculate X Y coordinates
//     *coordinates = convertToKiloMeters(make_pair(dLat,rLon));
 }

Edge_T createEdge(vector<std::string> line){
    Edge_T edge;

    edge.ID = stoul(line.at(0));
    edge.node1 = stoul(line.at(1));
    edge.node2 = stoul(line.at(2));

    return edge;
}

bool loadPlaces(GarbageManagement &management) {
    fstream places;
    unsigned long placeID;
    pair <double,double> coordinates;
    vector<std::string> lineVector;

    if(!openFile(places, PLACES_FILEPATH)){
        return false;
    }

    while(readLine(places, &lineVector)){

        if(lineVector.size() < 5){
            return false;
        }

        setPlace(lineVector, &placeID, &coordinates);
        building = lineVector.size() > 5 ? getBuildingType(lineVector.at(5)) : none;

        switch(building){
            case container:{
                type = lineVector.size() > 6 ? getGarbageType(lineVector.at(6)) : generic;
                management.addContainer(new Container(placeID, coordinates, type,0));
                break;
            }
            case station:{
                type = lineVector.size() > 6 ? getGarbageType(lineVector.at(6)) : generic;
                management.addStation(new Station(placeID, coordinates, type,0));
                break;
            }
            case garage:{
                management.addGarage(new Garage(placeID, coordinates));
                break;
            }
            default:{
                management.addPlace(new Place(placeID, coordinates));
                break;
            }
        }
    }

    places.close();

    std::cout << management.getGraph().getNumNodes() << " places were successfully read!\n";

    std::cout << management.getContainers().size() << " containers || ";
    std::cout << management.getStations().size() << " stations || ";
    std::cout << management.getGarages().size() << " garages\n\n";
    return true;
}

bool loadBuildings(GarbageManagement &management){
    return loadContainers(management) && loadStations(management) && loadGarages(management);
}

bool loadContainers(GarbageManagement &management){
    fstream containers;
    vector<std::string> lineVector;


    if(!openFile(containers, CONTAINERS_FILEPATH)){
        return false;
    }

    while(readLine(containers, &lineVector)){

    }

    containers.close();
    return true;
}

bool loadStations(GarbageManagement &management){
    fstream stations;
    vector<std::string> lineVector;

    if(!openFile(stations, STATIONS_FILEPATH)){
        return false;
    }

    while(readLine(stations, &lineVector)){

    }

    stations.close();
    return true;
}

bool loadGarages(GarbageManagement &management){
    fstream garages;
    vector<std::string> lineVector;

    if(!openFile(garages, STATIONS_FILEPATH)){
        return false;
    }

    while(readLine(garages, &lineVector)){

    }

    garages.close();
    return true;
}

bool loadEdges(GarbageManagement &management) {
    fstream edges;
    vector<std::string> lineVector;

    if(!openFile(edges, EDGES_FILEPATH)){
        return false;
    }

    while(readLine(edges, &lineVector)){

        if(lineVector.size() != 3){
            return false;
        }

        edgesVector.push_back(createEdge(lineVector));
    }

    edges.close();

    std::cout << edgesVector.size() << " edges were successfully read!\n\n";

    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream edgesInfo;
    unsigned long int id=0, nEdgesInfo=0;
    string name;
    vector<std::string> lineVector;
    EdgeType type;

    if(!openFile(edgesInfo, EDGES_INFO_FILEPATH)){
        return false;
    }

    while(readLine(edgesInfo, &lineVector)){

        if(lineVector.size() != 3){
            return false;
        }

        id = stoul(lineVector.at(0));

        for(Edge_T edge : edgesVector){
            if(edge.ID == id){
                pair <unsigned long int,unsigned long int> nodes
                        = make_pair(edge.node1,edge.node2);
                name = lineVector.at(1);
                type = lineVector.at(2) == "True" ? twoWay : oneWay;
                management.addEdge(0,nodes,type, name);
            }
        }
        nEdgesInfo++;
    }

    edgesInfo.close();

    std::cout << nEdgesInfo << " edges info info were successfully read!\n\n";
    return true;
}

bool loadVehicles(GarbageManagement &management){
    fstream vehicles;
    vector<std::string> lineVector;
    unsigned long int nVehicles=0;

    if(!openFile(vehicles, VEHICLES_FILEPATH)){
        return false;
    }

    while(readLine(vehicles, &lineVector)) {

        nVehicles++;
    }

    vehicles.close();

    std::cout << nVehicles << " vehicles were successfully read!\n\n";
    return true;
}

void saveNodes(const GarbageManagement &management) {

}

void saveEdges(const GarbageManagement &management) {

}

void saveEdgesInfo(const GarbageManagement &management) {

}
