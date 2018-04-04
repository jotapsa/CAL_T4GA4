#include "Graph.h"
#include "Node.h"

Graph::Graph() {
  this->nodeSet = std::vector<Node*>();
}

int Graph::getNumNodes() const {
  return nodeSet.size();
}

std::vector<Node *> Graph::getNodeSet() const {
  return nodeSet;
}

/*
 * Auxiliary function to find a node with a given id.
 */
Node * Graph::findNode(const unsigned long &id) const {

  for(auto n : nodeSet) {
    if (n->getId() == id)
      return n;
  }

  return NULL;
}

Street *Graph::findStreet(const unsigned long &id) {
  for(auto s : streets) {
    if (s->getId() == id)
      return s;
  }

  return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addNode(Node &node) {
  if(findNode(node.getId()) != NULL)
    return false;

  nodeSet.push_back(&node);

  return true;
}

bool Graph::addStreet(Street &street) {
  if(findNode(street.getId()) != NULL)
    return false;

  streets.push_back(&street);

  return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices.
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const unsigned long &sourc, const unsigned long &dest) {
  auto v1 = findNode(sourc);
  auto v2 = findNode(dest);
  if (v1 == NULL || v2 == NULL)
    return false;
  v1->addEdge(v2);
  return true;
}