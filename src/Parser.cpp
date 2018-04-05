#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

struct edge {
    unsigned long int ID, node1, node2;
};

std::vector<edge> edges;

std::vector<std::string> split(const std::string &s, const char &delim){
    std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);

    std::string partX;

    while(getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }

    return splitStrings;
}

BuildingType getBuildingType(string type){
    if(type.compare(string("container")) == 0){
        return container;
    }
    else if(type.compare(string("station")) == 0){
        return station;
    }
    else if(type.compare(string("garage")) == 0){
        cout << "comparing garage..." << endl;
        return garage;
    }
    else{
        //TODO
    }
}

garbageType getGarbageType(string type){
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

bool loadNodes(GarbageManagement &management) {
    fstream file;
    unsigned long nodeID;
    double dLon, dLat, rLon, rLat;
    string type, line;
    BuildingType building;
    pair <double,double> coordinates;
    vector<std::string> lineVector;

    file.open(NODES_FILEPATH, std::ios::in);

    if(!file.is_open()) {
        cout << "File " << NODES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << NODES_FILEPATH << endl;

    while(getline(file,line)){
        lineVector = split(line, ';');

        if(lineVector.size() < 5){
            return false;
        }

        nodeID = stoul(lineVector.at(0));

        dLat = stod(lineVector.at(1));
        dLon = stod(lineVector.at(2));
        rLat = stod(lineVector.at(3));
        rLon = stod(lineVector.at(4));

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);

        building = lineVector.size() > 5 ? getBuildingType(lineVector.at(5)) : none;

        switch(building){
            case container:{
                type = lineVector.at(6);
                management.addContainer(new Container(new Node(nodeID, coordinates), getGarbageType(type),0));
                break;
            }
            case station:{
                type = lineVector.at(6);
                management.addStation(new Station(new Node(nodeID, coordinates),getGarbageType(type),0));
                break;
            }
            case garage:{
                cout << "garagem" << endl;
                management.addGarage(new Garage(new Node(nodeID, coordinates)));
                return false;
                break;
            }
            default: {
                management.addNode(new Node(nodeID, coordinates));
                break;
            }
        }

        lineVector.clear();
    }

    file.close();

    std::cout << management.getGraph().getNumNodes() << " nodes were successfully read!\n\n";

    return true;
}

bool loadEdges(GarbageManagement &management) {
    fstream file;
    std::string line;
    vector<std::string> lineVector;

    file.open(EDGES_FILEPATH, std::ios::in);

    if(!file.is_open()) {
        cout << "File " << EDGES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << EDGES_FILEPATH << endl;

    while(getline(file,line)){
        lineVector = split(line,';');

        if(lineVector.size() != 3){
            return false;
        }

        edge Edge;

        Edge.ID = stoul(lineVector.at(0));
        Edge.node1 = stoul(lineVector.at(1));
        Edge.node2 = stoul(lineVector.at(2));

        edges.push_back(Edge);
    }

    file.close();

    std::cout << edges.size() << " edges were successfully read!\n\n";

    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream file;
    unsigned long int id=0, nEdgesInfo=0;
    string name;
    vector<std::string> lineVector;
    std::string line;
    EdgeType type;

    file.open(EDGES_INFO_FILEPATH, std::ios::in);

    if(!file.is_open()) {
        cout << "File " << EDGES_INFO_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << EDGES_INFO_FILEPATH << endl;

    while(getline(file,line)){
        lineVector = split(line,';');

        if(lineVector.size() != 3){
            return false;
        }

        id = stoul(lineVector.at(0));

        for(edge Edge : edges){
            if(Edge.ID == id){
                pair <unsigned long int,unsigned long int> nodes = make_pair(Edge.node1,Edge.node2);
                name = lineVector.at(1);
                type = lineVector.at(2) == "True" ? twoWay : oneWay;
                management.addEdge(0,nodes,type, name);
            }
        }
        nEdgesInfo++;
    }

    file.close();

    std::cout << nEdgesInfo << " edges info were successfully read!\n\n";

    return true;
}

void saveNodes(const GarbageManagement &management) {

}

void saveEdges(const GarbageManagement &management) {

}

void saveEdgesInfo(const GarbageManagement &management) {

}
