#ifndef _EDGE_H
#define _EDGE_H

#include "Node.h"

class Node;

class Edge {
private:
  Node *dest;      // destination vertex
public:
    Edge(Node *d);
    Node getDestination();
};

#endif
