//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_EDGE_H
#define CAL_T4GA4_EDGE_H

#include "Node.h"

class Node;

class Edge {
private:
  Node* dest;      // destination vertex
  double weight;         // edge weight
public:
    Edge(Node *d, double w);
    Node getDestination();
    double getWeight();
    friend class Graph;
    friend class Vertex;
};

#endif //CAL_T4GA4_EDGE_H
