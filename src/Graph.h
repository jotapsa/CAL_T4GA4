#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Street.h"
#include "Container.h"
#include "Node.h"
#include "Building.h"

class Graph {
private:
	std::vector<Node *> nodeSet;    // vertex set

    std::vector<Street *> streets;
	std::vector<Building *> containers;
public:
	Graph();
	int getNumNodes() const;

	std::vector<Node*> getNodeSet() const;
    std::vector<Street *> getStreets(){return this->streets;}
	std::vector<Building *> getContainers(){return this->containers;}

	Node *findNode(const unsigned long &id) const;
	Street* findStreet(const unsigned long &id) const;

	bool addNode(Node &node);
	bool addStreet(Street &street);
	bool addContainer(Container &container);
	bool addEdge(const unsigned long &sourc, const unsigned long &dest);
};

#endif /* GRAPH_H_ */
