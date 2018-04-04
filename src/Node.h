#ifndef _NODE_H
#define _NODE_H

#include <string>
#include <vector>
#include "Edge.h"

class Edge;

class Node {
  unsigned long id;                       // vertex Id
  std::pair<double, double> coordinates;
  std::vector<Edge> adj;  // outgoing edges
  void addEdge(Node *dest, double w);

public:
  Node(unsigned long in, std::pair<double, double> coordinates);
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
