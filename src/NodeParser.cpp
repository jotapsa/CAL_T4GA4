#include "NodeParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Aux.h"

using namespace std;

stringstream fileStream;
string info;

std::vector<std::string> split(const std::string &s, const char &delim){
    std::vector<std::string> splitStrings;
    std::istringstream inSStream(s);

    std::string partX;

    while (getline(inSStream, partX, delim)) {
        splitStrings.push_back (partX);
    }

    return splitStrings;
}

BuildingType getBuildingType(string type){
    if(type == "container"){
        return container;
    }
    else if(type == "station"){
        return station;
    }
    else if(type == "garage"){
        return garage;
    }
    else{
//        return BuildingType.none;
    }
}

garbageType getGarbageType(string type){
    if(type == "glass"){
        return glass;
    }
    else if(type == "plastic"){
        return plastic;
    }
    else if(type == "paper"){
        return paper;
    }
    else if(type == "generic"){
        return generic;
    }
    else{
//        return garbageType.none;
    }
}

bool loadNodes(Graph &graph) {
    fstream file;
    unsigned long nodeID;
    double dLon, dLat, rLon, rLat;
    string building, type, line;
    pair <double,double> coordinates;
    vector<std::string> lineVector;

    file.open(NODES_FILEPATH, std::ios::in);

    if(!file.is_open()) {
        cout << "File " << NODES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << NODES_FILEPATH << endl;

    while(getline(file,line)){

    }

    while(!file.eof()) {

        nodeID = stoul(lineVector.at(0));

        dLat = stod(lineVector.at(1));
        dLon = stod(lineVector.at(2));
        rLat = stod(lineVector.at(3));
        rLon = stod(lineVector.at(4));

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);
        Node* node = new Node(nodeID, coordinates);
        if(!graph.addNode(*node)){
            return false;
        }

        if(lineVector.size() == 5){
            continue;
        }

        building = lineVector.at(5);

        switch(getBuildingType(building)){
            case container:{
                type = lineVector.at(6);
//                if(!graph.addContainer(*(new Container(*node, getGarbageType(type),0)))){
//                    return false;
//                }
            }
                break;
            case station:
                break;
            case garage:
                break;
            default:
                return false;
        }

        building.clear();
    }

    file.close();

    return true;
}

bool loadEdges(Graph &graph) {
    fstream file;
    Node *n1, *n2;
    unsigned long int id=0, n1_id=0, n2_id=0;
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

        id = stoul(lineVector.at(0));
        n1_id = stoul(lineVector.at(1));
        n2_id = stoul(lineVector.at(2));

        n1 = graph.findNode(n1_id);
        n2 = graph.findNode(n2_id);

        if(n1 == nullptr || n2 == nullptr){
            return false;
        }

        if(!graph.addStreet(*(new Street(id,*n1,*n2)))){
            return false;
        }
    }

    file.close();

    return true;
}

bool loadEdgesInfo(Graph &graph) {
    fstream file;
    unsigned long int id=0;
    string name;
    EdgeType type;
    Street* street;
    vector<std::string> lineVector;
    std::string line;

    file.open(EDGES_INFO_FILEPATH, std::ios::in);

    if(!file.is_open()) {
        cout << "File " << EDGES_INFO_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << EDGES_INFO_FILEPATH << endl;

    while(getline(file,line)){
        if(lineVector.size() != 3){
            return false;
        }
        id = stoul(lineVector.at(0));

        street = graph.findStreet(id);
        if(street == nullptr){
            return false;
        }

        name = lineVector.at(1);
        type = lineVector.at(2) == "True" ? undirected : directed;

        street->setName(name);
        street->setEdgeType(type);
    }

    file.close();

    return true;
}
