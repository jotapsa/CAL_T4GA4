#include <iostream>
#include <fstream>
#include <sstream>
#include "GraphViewer.h"
#include "Graph.h"
#include "Cli.h"
#include "EdgeType.h"
#include "GarbageManagement.h"
//
//void clearStreams(stringstream &s, string &info) {
//  s.clear();
//  info.clear();
//}
//
//bool readNodes(char *filePath, Graph &graph) {
//
//  fstream file;
//  stringstream fileStream;
//  unsigned long vertexID;
//  double dLon, dLat, rLon, rLat;
//  std::string info;
//
//  file.open(filePath);
//
//  if(!file.is_open()) {
//    cout << "File " << filePath << " could not be open! \n";
//    return false;
//  }
//
//  std::cout << "Reading vertex file: " << filePath << endl;
//
//  while(file.eof() == false) {
//
//    clearStreams(fileStream, info);
//
//    if(getline(file, info, ';')) {
//      fileStream << info;
//      fileStream >> vertexID;
//      clearStreams(fileStream, info);
//    }
//
//    if(getline(file, info, ';')) {
//      fileStream << info;
//      fileStream >> dLat;
//      clearStreams(fileStream, info);
//    }
//
//    if(getline(file, info, ';')) {
//      fileStream << info;
//      fileStream >> dLon;
//      clearStreams(fileStream, info);
//    }
//
//    if(getline(file, info, ';')) {
//      fileStream << info;
//      fileStream >> rLon;
//      clearStreams(fileStream, info);
//    }
//
//    if(getline(file, info)) {
//      fileStream << info;
//      fileStream >> rLon;
//      clearStreams(fileStream, info);
//    }
//
//
//    graph.addVertex(vertexID, *toInsert);
//  }
//
//  file.close();
//
//  return true;
//}
//
//bool readStreetNames(char* filePath, std::vector<Street*> &streetsVector) {
//
//  fstream file;
//  stringstream fileStream;
//  std::string line;
//  unsigned long streetID;
//  std::string roadName;
//  int edgeType;
//  Street *toInsert;
//
//  file.open(filePath);
//
//  if(!file.is_open()) {
//    cout << "File " << filePath << " could not be open! \n";
//    return false;
//  }
//
//  std::cout << "Reading roads file: " << filePath << endl;
//
//  while(file.eof() == false) {
//
//    clearStreams(fileStream, line);
//
//    if(getline(file, line, ';')) {
//      fileStream << line;
//      fileStream >> streetID;
//      clearStreams(fileStream, line);
//    }
//
//    if(getline(file, line, ';')) {
//      roadName = std::string(line);
//      clearStreams(fileStream, line);
//    }
//
//    if(getline(file, line)) {
//      if(line.compare("True") == true) {
//        edgeType = UNDIRECTED;
//      }
//      else {
//        edgeType = DIRECTED;
//      }
//    }
//
//    toInsert = new Street(streetID, roadName, edgeType);
//
//    streetsVector.push_back(toInsert);
//  }
//
//  return true;
//}
//
//Node* getNode(std::vector<Node *> &nodesVector, unsigned long id){
//  for(unsigned int i = 0; i < nodesVector.size(); i++){
//    if(nodesVector[i]->getId() == id)
//      return nodesVector[i];
//  }
//  return NULL;
//}
//
//Street* getStreet(std::vector<Street*> &streetsVector, unsigned long id){
//  for(unsigned int i = 0; i < streetsVector.size(); i++){
//    if(streetsVector[i]->getId() == id)
//      return streetsVector[i];
//  }
//  return NULL;
//}
//
//bool readEdges(char* filePath, std::vector<Node *> nodesVector ,std::vector<Street*> &streetsVector, int *nSubRoads) {
//  //TODO read edges to a vector from "CAL_subroads.txt" (associates 2 vertixId to an edge).
//  fstream file;
//  stringstream fileStream;
//  std::string line;
//  int streetID, node1_ID, node2_ID;
//  file.open(filePath);
//  Street *street;
//
//  if(!file.is_open()) {
//    cout << "File " << filePath << " could not be open! \n";
//    return false;
//  }
//
//  std::cout << "Reading subroads file: " << filePath << endl;
//
//  while(file.eof() == false){
//    clearStreams(fileStream, line);
//
//    if(getline(file, line, ';')) {
//      fileStream << line;
//      fileStream >> streetID;
//      clearStreams(fileStream, line);
//    }
//
//    if(getline(file, line, ';')) {
//      fileStream << line;
//      fileStream >> node1_ID;
//      clearStreams(fileStream, line);
//    }
//
//    if(getline(file, line, ';')) {
//      fileStream << line;
//      fileStream >> node2_ID;
//      clearStreams(fileStream, line);
//    }
//
//    street = getStreet(streetsVector, streetID);
//    street->addNodes(getNode(nodesVector,node1_ID), getNode(nodesVector,node2_ID));
//
//    (*nSubRoads)++;
//  }
//
//  return true;
//}

int main (int argc, char* argv[]) {
//  Graph nodesGraph = Graph();
////
////  std::vector<Street *> streets = std::vector<Street *>();
////
////  if(readNodes(NODES_FILEPATH, nodesGraph)) {
////    std::cout << nodesGraph.getNumVertex() << " nodes were successfully read!\n";
////  }
////  else {
////    std::cout << "Failed to read nodes from file: " << NODES_FILEPATH << endl;
////  }
////
////  if(readStreetNames(ROADS_FILEPATH, streets)) {
////    std::cout << streets.size() << " streets were successfully read!!\n";
////  }
////  else {
////    std::cout << "Failed to read streets nodes from file: " << ROADS_FILEPATH << endl;
////  }
////
////  int nSubRoads=0;
////
////  if(readEdges(SUBROADS_FILEPATH, nodesGraph.getVertexSet(),streets, &nSubRoads)){
////    std::cout << nSubRoads << " subroads were successfully read!!\n";
////  }
////  else {
////    std::cout << "Failed to read subroads nodes from file: " << SUBROADS_FILEPATH << endl;
////  }
////
////  std::cout << streets.at(0)->getFirstNode()->getId() << endl;
////
////  Cli *cli = new Cli();
////
////  cli->menu();

    GarbageManagement* management = new GarbageManagement();

  return 0;
}
