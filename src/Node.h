#ifndef _NODE_H
#define _NODE_H

#include <string>
#include <vector>
#include "Edge.h"


class Node {
private:
  unsigned long ID;                       // vertex Id
  std::pair<double, double> coordinates;
  std::vector<Edge> edges;  // outgoing edges

public:
  Node(unsigned long ID, std::pair<double, double> coordinates);

  unsigned long getID() const;
  std::pair<double, double> getCoordinates();

  void addEdge(Node *n, double w);
};

#endif //_NODE_H
