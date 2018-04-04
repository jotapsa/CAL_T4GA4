#include "Node.h"

Node::Node(unsigned long in, std::pair<double, double> coordinates) {
  this->id = in;
  this->coordinates = coordinates;
}

unsigned long Node::getId() const {
  return this->id;
}

std::pair<double, double> Node::getCoordinates() {
  return this->coordinates;
};

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d).
 */
void Node::addEdge(Node *d) {
  adj.push_back(Edge(d));
}

