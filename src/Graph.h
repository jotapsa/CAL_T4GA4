#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class MutablePriorityQueue;
class Node;
class Edge;
class Road;


class Graph {
private:
	std::vector<Node *> nodeSet;    // vertex set

public:
	Graph();
	int getNumNodes() const;
	std::vector<Node*> getNodeSet() const;
	Node *findNode(const unsigned long &id) const;
	bool addNode(Node &node);
	bool addEdge(const unsigned long &sourc, const unsigned long &dest, double w);
};

#endif /* GRAPH_H_ */
