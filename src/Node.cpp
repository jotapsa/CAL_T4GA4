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
 * with a given destination vertex (d).
 */
void Node::addEdge(Node *d) {
//  adj.push_back(Edge(d));
}

