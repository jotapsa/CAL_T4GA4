/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Location.h"

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T id;                       // vertex Id
  Location coordinates;
	std::vector<Edge<T> > adj;  // outgoing edges
	bool visited;               // auxiliary field
	double dist = 0;            //algorithm distance
	double geoDist = 0;         //geo distance to source vertex for A*
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		    // required by MutablePriorityQueue
	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in, Location l);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getId() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, Location l) {
  this->id = in;
  this->coordinates = l;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getId() const {
	return this->id;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	std::vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	std::vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	bool relax(Vertex<T> * vertex, Vertex<T> *w, double weight);
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
  std::vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
  std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->id == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
bool Graph<T>::relax(Vertex<T> * vertex, Vertex<T> *w, double weight) {

	if(vertex->dist + weight < w->dist) {
		w->dist = vertex->dist + weight;

		w->path = vertex;

		return true;
	}
	else
		return false;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin)
{
	Vertex<T>  *source = findVertex(origin);

	Vertex<T> * min;

	if(source == NULL)
		return;

	for(auto v: vertexSet){
		v->dist = std::numeric_limits<double>::max();
		v->path = NULL;
	}

	MutablePriorityQueue<Vertex<T> > q;

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

template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
  std::vector<T> res;

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

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

	for(auto v : vertexSet){
		v->dist = INF;
		v->path = nullptr;
	}

	auto s = findVertex(orig);

	if(s == nullptr)
		return;

	MutablePriorityQueue<Vertex<T>> q;

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

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {

	Vertex<T>  *source = findVertex(orig);

	if(source == NULL)
		return;

	for(auto v: vertexSet){
		v->dist = INF;
		v->path = NULL;
	}

	MutablePriorityQueue<Vertex<T> > q;

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
