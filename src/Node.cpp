#include "Node.h"

Node::Node(unsigned long ID, std::pair<double, double> coordinates) {
  this->ID = ID;
  this->coordinates = coordinates;
}

unsigned long Node::getID() const {
  return this->ID;
}

std::pair<double, double> Node::getCoordinates() {
  return this->coordinates;
};

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination node (n) and edge weight (w).
 */
void Node::addEdge(Node *n, double w) {
  edges.emplace_back(n, w); //emplace_back adds a *new* element to the end of the container
}

