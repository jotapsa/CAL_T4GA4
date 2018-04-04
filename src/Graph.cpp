#include "Graph.h"
#include "Node.h"
#include <iostream>

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
Node* Graph::findNode(const unsigned long &id) const {
  for(auto node : nodeSet) {
    if (node->getID() == id)
      return node;
  }

  return NULL;
}

Street* Graph::findStreet(const unsigned long &id) const{
  for(auto street : streets) {
    if (street->getID() == id)
      return street;
  }

  return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addNode(Node &node) {
  if(findNode(node.getID()) != NULL){
    return false;
  }

  nodeSet.push_back(&node);
  return true;
}

bool Graph::addStreet(Street &street) {
//  if(findStreet(street.getID()) != NULL)
//    return false;

  streets.push_back(&street);
  return true;
}

bool Graph::addContainer(Container &container) {
    if(findNode(container.getNode()->getID()) == NULL){
      return false;
    }

    containers.push_back(&container);
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