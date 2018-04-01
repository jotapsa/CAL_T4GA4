//
// Created by dnc on 31-03-2018.
//

#include "Vertex.h"

class Location;

Vertex::Vertex(unsigned long in, Location *l, Location coordinates) : coordinates(coordinates) {
  this->id = in;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, double w) {
  adj.push_back(Edge(d, w));
}

bool Vertex::operator<(Vertex & vertex) const {
  return this->dist < vertex.dist;
}

unsigned long Vertex::getId() const {
  return this->id;
}

double Vertex::getDist() const {
  return this->dist;
}


Vertex *Vertex::getPath() const {
  return this->path;
}

Location  Vertex::getLocation() const {
  return this->coordinates;
}