#include "Node.h"

class Location;

Node::Node(unsigned long in, std::pair<double, double> coordinates) {
  this->id = in;
  this->coordinates.first = coordinates.first;
  this->coordinates.second = coordinates.second;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Node::addEdge(Node *d, double w) {
  adj.push_back(Edge(d, w));
}

bool Node::operator<(Node & vertex) const {
  return this->dist < vertex.dist;
}

unsigned long Node::getId() const {
  return this->id;
}

double Node::getDist() const {
  return this->dist;
}


Node *Node::getPath() const {
  return this->path;
}

void Node::setPath(Node *v)
{
  this->path = v;
}

std::pair<double, double> Node::getCoordinates() {
  return this->coordinates;
};
