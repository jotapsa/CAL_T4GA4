//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_VERTEX_H
#define CAL_T4GA4_VERTEX_H

#include <string>
#include <iostream>
#include "Location.h"
#include "MutablePriorityQueue.h"
#include "Edge.h"

class Edge;
class Location;

class Vertex {
  unsigned long id;                       // vertex Id
  Location coordinates = Location(0, 0, 0, 0);       // vertex coordinates
  std::vector<Edge> adj;  // outgoing edges
  bool visited;               // auxiliary field
  double dist = 0;            //algorithm distance
  double geoDist = 0;         //geo distance to source vertex for A*
  Vertex *path = NULL;
  bool processing = false;
  void addEdge(Vertex *dest, double w);

public:
  int queueIndex = 0; 		    // required by MutablePriorityQueue
  Vertex(unsigned long in, Location &l);
  bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
  unsigned long getId() const;
  double getDist() const;
  Vertex *getPath() const;
  void setPath(Vertex *v);
  Location  getLocation() const;
  void print();
  friend class Graph;
  friend class MutablePriorityQueue;
  friend class Edge;
};


#endif //CAL_T4GA4_VERTEX_H
