#include "NodeParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void clearStreams(stringstream &s, string &info) {
    s.clear();
    info.clear();
}

bool NodeParser::loadNodes(Graph &graph) {
    fstream file;
    stringstream fileStream;
    unsigned long nodeID;
    double dLon, dLat, rLon, rLat;
    std::string info;
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
            fileStream >> rLon;
            clearStreams(fileStream, info);
        }

        if(getline(file, info)) {
            fileStream << info;
            fileStream >> rLon;
            clearStreams(fileStream, info);
        }

        //TODO calculate X Y coordinates
        coordinates = make_pair(dLat,rLon);
        Node* node = new Node(nodeID, coordinates);

        graph.addNode(*node);
    }

    file.close();

    return true;
}

bool NodeParser::loadEdges(Graph &graph) {

}

bool NodeParser::loadEdgesInfo(Graph &graph) {

}
