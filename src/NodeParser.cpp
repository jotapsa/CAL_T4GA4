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

    std::cout << "Reading vertex file: " << NODES_FILEPATH << endl;

    while(file.eof() == false) {

        clearStreams(fileStream, info);

        nodeID = readInt(file);

        dLat = readDouble(file);
        dLon = readDouble(file);
        rLat = readDouble(file);
        rLon = readDouble(file);

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);
        Node* node = new Node(nodeID, coordinates);
        graph.addNode(*node);

        building = readString(file);

        if(building.length() > 0){
            switch(getBuildingType(building)){
                case container:{
                    type = readString(file);
                    graph.addContainer(*(new Container(*node, getGarbageType(type),0)));
                }
                    break;
                case station:
                    break;
                case garage:
                    break;
                default:
                    return false;
            }
            cout << building << endl;
        }


        building.clear();
    }

    file.close();

    return true;
}

bool loadEdges(Graph &graph) {
    return true;
}

bool loadEdgesInfo(Graph &graph) {
    return true;
}
