/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Edge.h"
#include "Street.h"
#include "Node.h"

#define INF std::numeric_limits<double>::max()

class MutablePriorityQueue;
class Node;
class Edge;
class Road;


class Graph {
	std::vector<Node *> vertexSet;    // vertex set

public:
	Graph();
	Node *findVertex(const unsigned long &id) const;
	bool addVertex(const unsigned long &in, Location &coord);
	bool addEdge(const unsigned long &sourc, const unsigned long &dest, double w);
	int getNumVertex() const;
	std::vector<Node*> getVertexSet() const;
};

#endif /* GRAPH_H_ */
