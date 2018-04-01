/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Location.h"
#include "Vertex.h"
#include "Edge.h"
#include "Street.h"

#define INF std::numeric_limits<double>::max()

class Graph {
	std::vector<Vertex *> vertexSet;    // vertex set

public:
	Vertex *findVertex(const unsigned long &id) const;
	bool addVertex(const unsigned long &in, const Location &coord);
	bool addEdge(const Vertex &sourc, const Vertex &dest, double w);
	int getNumVertex() const;
	std::vector<Vertex *> getVertexSet() const;
	std::vector<Vertex *> getPath(const unsigned long &origin, const unsigned long &dest);
	bool relax(Vertex * vertex, Vertex *w, double weight);
	void dijkstraShortestPath(const unsigned long &s);
	void unweightedShortestPath(const unsigned long &s);
	void bellmanFordShortestPath(const unsigned long &s);
	void floydWarshallShortestPath();
  std::vector getfloydWarshallPath(const unsigned long &origin, const unsigned long &dest) const;

};

int Graph::getNumVertex() const {
	return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const unsigned long &in) const {
	for (auto v : vertexSet)
		if (v->id == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const unsigned long &in, const Location &coord) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in, coord, Location(0, 0, 0, 0)));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const Vertex &sourc, const Vertex &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

bool Graph::relax(Vertex * vertex, Vertex *w, double weight) {

	if(vertex->dist + weight < w->dist) {
		w->dist = vertex->dist + weight;

		w->getPath() = vertex;

		return true;
	}
	else
		return false;
}

void Graph::dijkstraShortestPath(const unsigned long &origin)
{
	Vertex  *source = findVertex(origin);

	Vertex *min;

	if(source == NULL)
		return;

	for(auto v: vertexSet) {
		v->dist = std::numeric_limits<double>::max();
		v->path = NULL;
	}

	MutablePriorityQueue<Vertex> q;

	source->dist = 0;

	q.insert(source);

	while(!q.empty()) {

		min = q.extractMin();

		for(auto e: min->adj) {

			auto oldDist = e.dest->dist;

			if(relax(min, e.dest, e.weight)) {

				if(oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}

std::vector Graph::getPath(const unsigned long &origin, const unsigned long &dest) const {

  std::vector<unsigned long> res;

	auto v = findVertex(dest);

	if(v == nullptr || v->dist == INF)
		return res;

	while(v != nullptr) {
		res.push_back(v->id);

		v = v->path;
	}

  std::reverse(res.begin(), res.end());

	return res;
}

void Graph::unweightedShortestPath(const unsigned long &orig) {

	for(auto v : vertexSet){
		v->dist = INF;
		v->path = nullptr;
	}

	auto s = findVertex(orig);

	if(s == nullptr)
		return;

	MutablePriorityQueue<Vertex> q;

	s->dist = 0;

	q.insert(s);

	while(!q.empty()){

		auto v = q.extractMin();

		for(auto edge: v->adj){

			if(edge.dest->dist == INF){
				q.insert(edge.dest);
				edge.dest->dist = v->dist + 1;
				edge.dest->path = v;
			}
		}
	}
}

void Graph::bellmanFordShortestPath(const unsigned long &orig) {

	Vertex *source = findVertex(orig);

	if(source == NULL)
		return;

	for(auto v: vertexSet){
		v->dist = INF;
		v->path = NULL;
	}

	MutablePriorityQueue<Vertex> q;

	source->dist = 0;

	for(size_t i = 0; i < vertexSet.size() - 1; i++)
	{
		for(auto v : vertexSet)
		{
			for(auto edge : v->adj)
			{
				auto oldDist = edge.dest->dist;

				if(v->dist + edge.weight < oldDist)
				{
					edge.dest->dist = v->dist + edge.weight;
					edge.dest->path = v;
				}
			}
		}
	}

}


/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
  std::vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
