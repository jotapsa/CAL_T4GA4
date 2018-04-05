#ifndef _EDGE_H
#define _EDGE_H

#include "Node.h"

class Node;

class Edge {
private:
    Node *dest;      // destination vertex
    double weight;
public:
    Edge(Node *d, double w);
    Node * getDestination();
    double getWeight();
};

#endif
