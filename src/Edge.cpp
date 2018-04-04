#include "Edge.h"

Edge::Edge(Node *d) {
  this->dest = d;

}

Node Edge::getDestination() {
  return *this->dest;
}