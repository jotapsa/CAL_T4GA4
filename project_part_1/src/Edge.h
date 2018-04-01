//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_EDGE_H
#define CAL_T4GA4_EDGE_H

#include "Vertex.h"

class Vertex;

class Edge {
private:
  Vertex* dest;      // destination vertex
  double weight;         // edge weight
public:
    Edge(Vertex *d, double w);
    Vertex getDestination();
    double getWeight();
    friend class Graph;
    friend class Vertex;
};

#endif //CAL_T4GA4_EDGE_H
