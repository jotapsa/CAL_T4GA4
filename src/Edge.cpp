//
// Created by dnc on 31-03-2018.
//

#include "Edge.h"

Edge::Edge(Node *d, double w) {
  this->dest = d;

  this->weight = w;
}

Node Edge::getDestination() {
  return *this->dest;
}

double Edge::getWeight() {
  return this->weight;
}