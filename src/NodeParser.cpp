#include "NodeParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Aux.h"

using namespace std;

stringstream fileStream;
string info;

void clearStreams(stringstream &s, string &info) {
    s.clear();
    info.clear();
}

unsigned long int readInt(fstream& file){
    unsigned long int i;

    if(getline(file, info, ';')) {
        fileStream << info;
        fileStream >> i;
        clearStreams(fileStream, info);
    }

    return i;
}

double readDouble(fstream& file){
    double d;

    if(getline(file, info, ';')) {
        fileStream << info;
        fileStream >> d;
        clearStreams(fileStream, info);
    }

    return d;
}

string readString(fstream& file){
    string s;

    if(getline(file, info, ';')) {
        fileStream << info;
        fileStream >> s;
        clearStreams(fileStream, info);
    }

    return s;
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
    string building, type;
    pair <double,double> coordinates;

    file.open(NODES_FILEPATH);

    if(!file.is_open()) {
        cout << "File " << NODES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << NODES_FILEPATH << endl;

    while(!file.eof()) {

        clearStreams(fileStream, info);

        nodeID = readInt(file);

        dLat = readDouble(file);
        dLon = readDouble(file);
        rLat = readDouble(file);
        rLon = readDouble(file);

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);
        Node* node = new Node(nodeID, coordinates);
        if(!graph.addNode(*node)){
            return false;
        }

        building = readString(file);

        if(building.length() > 0){
            switch(getBuildingType(building)){
                case container:{
                    type = readString(file);
                    if(!graph.addContainer(*(new Container(*node, getGarbageType(type),0)))){
                        return false;
                    }
                }
                    break;
                case station:
                    break;
                case garage:
                    break;
                default:
                    return false;
            }
//            cout << building << endl;
        }


        building.clear();
    }

    file.close();

    return true;
}

bool loadEdges(Graph &graph) {
    fstream file;
    Node *n1, *n2;
    unsigned long int id=0;

    file.open(EDGES_FILEPATH);

    if(!file.is_open()) {
        cout << "File " << EDGES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << EDGES_FILEPATH << endl;

    while(!file.eof()) {

        clearStreams(fileStream, info);

        id = readInt(file);

        n1 = graph.findNode(readInt(file));
        n2 = graph.findNode(readInt(file));

        cout << id << endl;

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

    file.open(EDGES_INFO_FILEPATH);

    if(!file.is_open()) {
        cout << "File " << EDGES_INFO_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading file: " << EDGES_INFO_FILEPATH << endl;

    while(!file.eof()) {

        clearStreams(fileStream, info);

        id = readInt(file);

        cout << id << endl;

        street = graph.findStreet(id);
        if(street == nullptr){
            return false;
        }

        name = readString(file);
        type = readString(file) == "True" ? undirected : directed;

        street->setName(name);
        street->setEdgeType(type);
    }

    file.close();

    return true;
}
