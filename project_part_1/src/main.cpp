//
// Created by dnc on 30-03-2018.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GraphViewer.h"
#include "Graph.h"
#include "Location.h"

#define RESOURCES_DIR "../resources/"

void clearStreams(stringstream &s, string &info) {
  s.clear();
  info.clear();
}

bool readNodesAndInsertThemToGraphs(char* fileName, Graph &graph) {

  fstream file;
  stringstream fileStream;
  unsigned long vertexID;
  double dLon, dLat, rLon, rLat;
  string info;
  Location *toInsert = new Location(0,0,0,0);

  file.open(std::string(RESOURCES_DIR) + fileName);

  if(!file.is_open()) {
    cout << "File " << fileName << " could not be open! \n";
    return false;
  }


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

    if(getline(file, info, ';')) {
      fileStream << info;
      fileStream >> rLon;
      clearStreams(fileStream, info);
    }

    toInsert = new Location(dLat,dLon,rLat,rLon);

    graph.addVertex(vertexID, *toInsert);
  }

  return true;
}

bool readStreetNames(char* fileName, std::vector<Street> &streetsVector) {

  //TODO read streets to a vector from "CAL_roads.txt".
  return true;
}

bool readEdges(char* fileName, std::vector<Edge> edgesVector) {

  //TODO read edges to a vector from "CAL_subroads.txt" (associates 2 vertixId to an edge).
  return true;
}

void exercicio2() {

  Graph *nodesGraph = new Graph();

  Location *x = new Location(1,1,1,1);

  nodesGraph->addVertex(1, *x);

    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);
    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
    gv->addEdge(2,2,3,EdgeType::UNDIRECTED);
    gv->addEdge(3,3,4,EdgeType::UNDIRECTED);
    gv->addEdge(4,4,5,EdgeType::UNDIRECTED);
    gv->addEdge(5,5,6,EdgeType::UNDIRECTED);
    gv->addEdge(6,6,7,EdgeType::UNDIRECTED);
    gv->addEdge(7,7,0,EdgeType::UNDIRECTED);
    gv->addEdge(8,4,9,EdgeType::UNDIRECTED);
    gv->addEdge(9,9,8,EdgeType::UNDIRECTED);
    gv->addEdge(10,9,10,EdgeType::UNDIRECTED);
    gv->addEdge(11,9,11,EdgeType::UNDIRECTED);
    gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
    gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
    gv->rearrange();

    sleep(1);

    for(int i = 0; i < 10; i++)
    {
        gv->removeEdge(12);
        gv->removeEdge(13);
        if(i % 2 == 0)
        {
            gv->removeNode(12);
            gv->removeNode(13);
            gv->addNode(14, 250, 550);
            gv->addNode(15, 350, 550);
            gv->addEdge(12,11,14,EdgeType::UNDIRECTED);
            gv->addEdge(13,11,15,EdgeType::UNDIRECTED);
        }
        else
        {
            gv->removeNode(14);
            gv->removeNode(15);
            gv->addNode(12, 200, 550);
            gv->addNode(13, 400, 550);
            gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
            gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
        }
        gv->rearrange();
        sleep(1);
    }
}

bool validNumberOfArgs(int numberOfArgs) {
  return (numberOfArgs == 4);
}

int main (int argc, char* argv[]) {

  if(!validNumberOfArgs(argc)) {
    std::cout << "Usage: <Program Name> <Vertix File> <Roads Info File> <Roads Connection File> \n";
    return 0;
  }

  Graph nodesGraph = Graph();

  std::vector<Street> streets;

  if(!readNodesAndInsertThemToGraphs(argv[1], nodesGraph))
    std::cout << "Erro ao ler nós!\n";
  else
    std::cout << nodesGraph.getNumVertex() << " nós lidos com sucesso!\n";


  //nodesGraph.printNodes();

  return 0;
}