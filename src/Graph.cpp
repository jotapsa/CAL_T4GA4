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
Node* Graph::getNode(const unsigned long &id) const {
    for(auto node : nodeSet) {
        if (node->getID() == id){
            return node;
        }
    }

  return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addNode(Node &node) {
  if(getNode(node.getID()) != nullptr){
    return false;
  }

    nodeSet.push_back(&node);
    return true;
}
