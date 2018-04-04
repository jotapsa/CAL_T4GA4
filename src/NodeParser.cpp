#include "NodeParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Aux.h"

using namespace std;

void clearStreams(stringstream &s, string &info) {
    s.clear();
    info.clear();
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
        return none;
    }
}

bool loadNodes(Graph &graph) {
    fstream file;
    stringstream fileStream;
    unsigned long nodeID;
    double dLon, dLat, rLon, rLat;
    string info, building, type;
    pair <double,double> coordinates;

    file.open(NODES_FILEPATH);

    if(!file.is_open()) {
        cout << "File " << NODES_FILEPATH << " could not be open! \n";
        return false;
    }

    std::cout << "Reading vertex file: " << NODES_FILEPATH << endl;

    while(file.eof() == false) {

        clearStreams(fileStream, info);

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> nodeID;
            clearStreams(fileStream, info);
        }

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> dLat;
            clearStreams(fileStream, info);
        }

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> dLon;
            clearStreams(fileStream, info);
        }

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> rLat;
            clearStreams(fileStream, info);
        }

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> rLon;
            clearStreams(fileStream, info);
        }

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);
        Node* node = new Node(nodeID, coordinates);
        graph.addNode(*node);

        if(getline(file, info, ';')) {
            fileStream << info;
            fileStream >> building;
            clearStreams(fileStream, info);
        }

        if(building.length() > 0){
            switch(getBuildingType(building)){
                case container:
                    break;
                case station:
                    break;
                case garage:
                    break;
                default:
                    break;
            }
            cout << building << endl;
        }


        building.clear();
    }

    file.close();

    return true;
}

bool loadEdges(Graph &graph) {

}

bool loadEdgesInfo(Graph &graph) {

}
