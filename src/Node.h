#ifndef _NODE_H
#define _NODE_H

#include <string>
#include <iostream>
#include "Location.h"
#include "MutablePriorityQueue.h"
#include "Edge.h"

class Edge;
class Location;

class Node {
  unsigned long id;                       // vertex Id
  Location coordinates = Location(0, 0, 0, 0);       // vertex coordinates
  std::vector<Edge> adj;  // outgoing edges
  bool visited;               // auxiliary field
  double dist = 0;            //algorithm distance
  double geoDist = 0;         //geo distance to source vertex for A*
  Node *path = NULL;
  bool processing = false;
  void addEdge(Node *dest, double w);

public:
  int queueIndex = 0; 		    // required by MutablePriorityQueue
  Node(unsigned long in, Location &l);
  bool operator<(Node & vertex) const; // // required by MutablePriorityQueue
  unsigned long getId() const;
  double getDist() const;
  Node *getPath() const;
  void setPath(Node *v);
  Location  getLocation() const;
  void print();
  friend class Graph;
  friend class MutablePriorityQueue;
  friend class Edge;
};


#endif //_NODE_H
