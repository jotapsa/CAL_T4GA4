#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Street.h"
#include "Node.h"

class Graph {
private:
	std::vector<Node *> nodeSet;    // vertex set

    std::vector<Street *> streets;
public:
	Graph();
	int getNumNodes() const;

	std::vector<Node*> getNodeSet() const;
    std::vector<Street *> getStreets(){return this->streets;}

	Node *findNode(const unsigned long &id) const;
	Street* findStreet(const unsigned long &id);

	bool addNode(Node &node);
	bool addStreet(Street &street);
	bool addEdge(const unsigned long &sourc, const unsigned long &dest);
};

#endif /* GRAPH_H_ */
