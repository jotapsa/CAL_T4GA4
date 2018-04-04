#include <iostream>
#include <fstream>
#include <sstream>
#include "GraphViewer.h"
#include "Graph.h"
#include "Cli.h"
#include "main.h"

void clearStreams(stringstream &s, string &info) {
  s.clear();
  info.clear();
}

bool readNodes(char *filePath, Graph &graph) {

  fstream file;
  stringstream fileStream;
  unsigned long vertexID;
  double dLon, dLat, rLon, rLat;
  std::string info;
  Location *toInsert = new Location(0,0,0,0);

  file.open(filePath);

  if(!file.is_open()) {
    cout << "File " << filePath << " could not be open! \n";
    return false;
  }

  std::cout << "Reading vertex file: " << filePath << endl;

  while(file.eof() == false) {

    clearStreams(fileStream, info);

    if(getline(file, info, ';')) {
      fileStream << info;
      fileStream >> vertexID;
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

    toInsert = new Location(dLat,dLon,rLat,rLon);

    graph.addVertex(vertexID, *toInsert);
  }

  file.close();

  return true;
}

bool readStreetNames(char* filePath, std::vector<Street*> &streetsVector) {

  fstream file;
  stringstream fileStream;
  std::string line;
  unsigned long streetID;
  std::string roadName;
  bool twoWay;
  Street *toInsert;

  file.open(filePath);

  if(!file.is_open()) {
    cout << "File " << filePath << " could not be open! \n";
    return false;
  }

  std::cout << "Reading roads file: " << filePath << endl;

  while(file.eof() == false) {

    clearStreams(fileStream, line);

    if(getline(file, line, ';')) {
      fileStream << line;
      fileStream >> streetID;
      clearStreams(fileStream, line);
    }

    if(getline(file, line, ';')) {
      roadName = std::string(line);
      clearStreams(fileStream, line);
    }

    if(getline(file, line)) {
      if(line.compare("True") == true) {
        twoWay = true;
      }
      else {
        twoWay = false;
      }
    }

    toInsert = new Street(streetID, roadName, twoWay);

    streetsVector.push_back(toInsert);
  }

  return true;
}

bool readEdges(char* filePath, Graph &graph, int *nSubRoads) {
  //TODO read edges to a vector from "CAL_subroads.txt" (associates 2 vertixId to an edge).
  fstream file;
  stringstream fileStream;
  std::string line;
  int nodeID, node1, node2;
  file.open(filePath);

  if(!file.is_open()) {
    cout << "File " << filePath << " could not be open! \n";
    return false;
  }

  std::cout << "Reading subroads file: " << filePath << endl;

  while(file.eof() == false){
    clearStreams(fileStream, line);

    if(getline(file, line, ';')) {
      fileStream << line;
      fileStream >> nodeID;
      clearStreams(fileStream, line);
    }

    if(getline(file, line, ';')) {
      fileStream << line;
      fileStream >> node1;
      clearStreams(fileStream, line);
    }

    if(getline(file, line, ';')) {
      fileStream << line;
      fileStream >> node2;
      clearStreams(fileStream, line);
    }

  }

  return true;
}

int main (int argc, char* argv[]) {
  Graph nodesGraph = Graph();

  std::vector<Street *> streets = std::vector<Street *>();

  if(readNodes(NODES_FILEPATH, nodesGraph)) {
    std::cout << nodesGraph.getNumVertex() << " nodes were successfully read!\n";
  }
  else {
    std::cout << "Failed to read nodes from file: " << NODES_FILEPATH << endl;
  }

  if(readStreetNames(ROADS_FILEPATH, streets)) {
    std::cout << streets.size() << " streets were successfully read!!\n";
  }
  else {
    std::cout << "Failed to read streets nodes from file: " << ROADS_FILEPATH << endl;
  }

  Cli *cli = new Cli();

  cli->menu();

//  nodesGraph.printNodes();
//
//  for(auto road: streets) {
//    std::cout << "Street: " << road->getName() << " with ID: " << road->getId();
//
//    if(road->isStreetTwoWay())
//      std::cout << " and it's a two way street.\n";
//    else
//      std::cout << " and it's a one way street.\n";
//  }
  int nSubRoads=0;

  if(readEdges(SUBROADS_FILEPATH,nodesGraph, &nSubRoads)){
    std::cout << nSubRoads << " subroads were successfully read!!\n";
  }
  else {
    std::cout << "Failed to read subroads nodes from file: " << SUBROADS_FILEPATH << endl;
  }

  return 0;
}

//void exercicio2() {
//
//  Graph *nodesGraph = new Graph();
//
//  Location *x = new Location(1,1,1,1);
//
//  nodesGraph->addVertex(1, *x);
//
//  GraphViewer *gv = new GraphViewer(600, 600, false);
//  gv->createWindow(600, 600);
//  gv->defineVertexColor("blue");
//  gv->defineEdgeColor("black");
//  gv->addNode(0, 300, 50);
//  gv->addNode(1, 318, 58);
//  gv->addNode(2, 325, 75);
//  gv->addNode(3, 318, 93);
//  gv->addNode(4, 300, 100);
//  gv->addNode(5, 282, 93);
//  gv->addNode(6, 275, 75);
//  gv->addNode(7, 282, 58);
//  gv->addNode(8, 150, 200);
//  gv->addNode(9, 300, 200);
//  gv->addNode(10, 450, 200);
//  gv->addNode(11, 300, 400);
//  gv->addNode(12, 200, 550);
//  gv->addNode(13, 400, 550);
//  gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
//  gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
//  gv->addEdge(2,2,3,EdgeType::UNDIRECTED);
//  gv->addEdge(3,3,4,EdgeType::UNDIRECTED);
//  gv->addEdge(4,4,5,EdgeType::UNDIRECTED);
//  gv->addEdge(5,5,6,EdgeType::UNDIRECTED);
//  gv->addEdge(6,6,7,EdgeType::UNDIRECTED);
//  gv->addEdge(7,7,0,EdgeType::UNDIRECTED);
//  gv->addEdge(8,4,9,EdgeType::UNDIRECTED);
//  gv->addEdge(9,9,8,EdgeType::UNDIRECTED);
//  gv->addEdge(10,9,10,EdgeType::UNDIRECTED);
//  gv->addEdge(11,9,11,EdgeType::UNDIRECTED);
//  gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
//  gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
//  gv->rearrange();
//
//  sleep(1);
//
//  for(int i = 0; i < 10; i++)
//  {
//    gv->removeEdge(12);
//    gv->removeEdge(13);
//    if(i % 2 == 0)
//    {
//      gv->removeNode(12);
//      gv->removeNode(13);
//      gv->addNode(14, 250, 550);
//      gv->addNode(15, 350, 550);
//      gv->addEdge(12,11,14,EdgeType::UNDIRECTED);
//      gv->addEdge(13,11,15,EdgeType::UNDIRECTED);
//    }
//    else
//    {
//      gv->removeNode(14);
//      gv->removeNode(15);
//      gv->addNode(12, 200, 550);
//      gv->addNode(13, 400, 550);
//      gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
//      gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
//    }
//    gv->rearrange();
//    sleep(1);
//  }
//}
