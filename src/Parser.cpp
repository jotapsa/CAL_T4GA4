#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

stringstream fileStream;
string info;

std::vector<Street> streets;


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
    if(strcmp(type.c_str(),"container") == 0){
        return container;
    }
    else if(strcmp(type.c_str(),"station") == 0){
        return station;
    }
    else if(strcmp(type.c_str(),"garage") == 0){
        return garage;
    }
    else{
//        return BuildingType.none;
    }
}

garbageType getGarbageType(string type){
    if(strcmp(type.c_str(),"glass") == 0){
        return glass;
    }
    else if(strcmp(type.c_str(),"plastic") == 0){
        return plastic;
    }
    else if(strcmp(type.c_str(),"paper") == 0){
        return paper;
    }
    else if(strcmp(type.c_str(),"generic") == 0){
        return generic;
    }
    else{
//        return garbageType.none;
    }
}

bool loadNodes(GarbageManagement &management) {
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
        Node* node = new Node(nodeID, coordinates);
        management.addNode(node);

        if(lineVector.size() == 5){
            continue;
        }

        building = lineVector.at(5);

        switch(getBuildingType(building)){
            case container:{
                type = lineVector.at(6);
                management.addContainer(new Container(*node, getGarbageType(type),0));
                break;
            }
            case station:{
                type = lineVector.at(6);
                management.addStation(new Station(*node,getGarbageType(type),0));
                break;
            }
            case garage:{
                type = lineVector.at(6);
//                management.addGarage(Garage(node,getGarbageType(type),0));
                break;
            }
            default:
                return false;
        }
    }

    file.close();

    std::cout << management.getGraph().getNumNodes() << " nodes were successfully read!\n\n";

    return true;
}

bool loadEdges(GarbageManagement &management) {
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

        if(lineVector.size() != 3){
            return false;
        }

        id = stoul(lineVector.at(0));
        n1_id = stoul(lineVector.at(1));
        n2_id = stoul(lineVector.at(2));

        streets.push_back(*(new Street(id,*n1,*n2)));

//        n1 = graph.findNode(n1_id);
//        n2 = graph.findNode(n2_id);
//
//        if(n1 == nullptr || n2 == nullptr){
//            return false;
//        }

//        if(!graph.addStreet(*(new Street(id,*n1,*n2)))){
//            return false;
//        }
    }

    file.close();

    std::cout << streets.size() << " edges were successfully read!\n\n";

    return true;
}

bool loadEdgesInfo(GarbageManagement &management) {
    fstream file;
    unsigned long int id=0, edges=0;
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
        lineVector = split(line,';');

        if(lineVector.size() != 3){
            return false;
        }

        id = stoul(lineVector.at(0));

        //--------- Temporary ---------
        Street *s;
        for(Street street : streets) {
            if (street.getID() == id)
                s = &street;
        }

//        street = graph.findStreet(id);
//        if(street == nullptr){
//            return false;
//        }

        name = lineVector.at(1);
        type = lineVector.at(2) == "True" ? undirected : directed;

        s->setName(name);
        s->setEdgeType(type);

        //--------- Temporary ---------
        edges++;
    }

    file.close();

    std::cout << edges << " edges info were successfully read!\n\n";

    return true;
}

void saveNodes(const GarbageManagement &management) {

}

void saveEdges(const GarbageManagement &management) {

}

void saveEdgesInfo(const GarbageManagement &management) {

}
