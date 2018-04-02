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
#include "Location.h"
#include "Vertex.h"
#include "MutablePriorityQueue.h"

#define INF std::numeric_limits<double>::max()

class MutablePriorityQueue;
class Vertex;
class Edge;
class Road;


class Graph {
	std::vector<Vertex *> vertexSet;    // vertex set

public:
	Graph();
	Vertex *findVertex(const unsigned long &id) const;
	bool addVertex(const unsigned long &in, Location &coord);
	bool addEdge(const unsigned long &sourc, const unsigned long &dest, double w);
	int getNumVertex() const;
	std::vector<Vertex*> getVertexSet() const;
	std::vector<unsigned long> getPath(const unsigned long &origin, const unsigned long &dest);
	bool relax(Vertex * vertex, Vertex *w, double weight);
	void dijkstraShortestPath(const unsigned long &s);
	void unweightedShortestPath(const unsigned long &s);
	void bellmanFordShortestPath(const unsigned long &s);
	void floydWarshallShortestPath();
  std::vector<unsigned long> getfloydWarshallPath(const unsigned long &origin, const unsigned long &dest) const;
};

#endif /* GRAPH_H_ */
