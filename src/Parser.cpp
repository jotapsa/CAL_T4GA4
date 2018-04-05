#include "Parser.h"
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

struct edge {
    unsigned long int ID, node1, node2;
};

std::vector<edge> edgesVector;
string line;
BuildingType building;
GarbageType type;

bool openFile(fstream& file, std::string filePath){
    file.open(filePath);

    if(!file.is_open()) {
        cout << "File " << filePath << " could not be open! \n";
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

bool readLine(fstream& file, vector<std::string> lineVector){
    if(!getline(file,line,'\r')){
        return false;
    }

    lineVector = split(line, ';');
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

Node* createNode(vector<std::string> line){
    unsigned long nodeID;
    double dLon, dLat, rLon, rLat;
    pair <double,double> coordinates;

    nodeID = stoul(line.at(0));

    dLat = stod(line.at(1));
    dLon = stod(line.at(2));
    rLat = stod(line.at(3));
    rLon = stod(line.at(4));

    //TODO calculate X Y coordinates
    coordinates = make_pair(dLat,rLon);

    return new Node(nodeID, coordinates);
}

bool loadNodes(GarbageManagement &management) {
    fstream nodes;
    vector<std::string> lineVector;

    if(!openFile(nodes, NODES_FILEPATH)){
        return false;
    }

    while(readLine(nodes, lineVector)){

        if(lineVector.size() < 5){
            return false;
        }

        management.addNode(createNode(lineVector));
    }

    nodes.close();

    std::cout << management.getGraph().getNumNodes() << " nodes were successfully read!\n\n";

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

    while(readLine(containers, lineVector)){
        building = lineVector.size() > 5 ? getBuildingType(lineVector.at(5)) : none;
        type = lineVector.size() > 6 ? getGarbageType(lineVector.at(6)) : generic;

        management.addContainer(new Container(createNode(lineVector), type,0));
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

    while(readLine(stations, lineVector)){
        building = lineVector.size() > 5 ? getBuildingType(lineVector.at(5)) : none;
        type = lineVector.size() > 6 ? getGarbageType(lineVector.at(6)) : generic;

        management.addStation(new Station(createNode(lineVector), type,0));
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

    while(readLine(garages, lineVector)){
        building = lineVector.size() > 5 ? getBuildingType(lineVector.at(5)) : none;

        management.addGarage(new Garage(createNode(lineVector)));
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

    while(readLine(edges, lineVector)){

        if(lineVector.size() != 3){
            return false;
        }

        edge Edge;

        Edge.ID = stoul(lineVector.at(0));
        Edge.node1 = stoul(lineVector.at(1));
        Edge.node2 = stoul(lineVector.at(2));

        edgesVector.push_back(Edge);
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

    while(readLine(edgesInfo, lineVector)){

        if(lineVector.size() != 3){
            return false;
        }

        id = stoul(lineVector.at(0));

        for(edge Edge : edgesVector){
            if(Edge.ID == id){
                pair <unsigned long int,unsigned long int> nodes = make_pair(Edge.node1,Edge.node2);
                name = lineVector.at(1);
                type = lineVector.at(2) == "True" ? twoWay : oneWay;
                management.addEdge(0,nodes,type, name);
            }
        }
        nEdgesInfo++;
    }

    edgesInfo.close();

    std::cout << nEdgesInfo << " edgesVector info were successfully read!\n\n";

    return true;
}

void saveNodes(const GarbageManagement &management) {

}

void saveEdges(const GarbageManagement &management) {

}

void saveEdgesInfo(const GarbageManagement &management) {

}
