#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "MutablePriorityQueue.h"
#include "EdgeType.h"
#include <vector>
#include <queue>
#include <limits>

template <class T> class Edge;
template <class T> class Graph;

//TODO: bfs, floyd warshall
//TODO: unweighted shortest path, A*
//TODO: Path finding optimizations.

template <class T>
class Graph {
private:
    std::vector<Node<T> *> nodeSet;    // Node set

    double ** W;   //minimum weight matrix
    int ** P;   //shortest path matrix

public:
    Node<T> * getNode(const T &in) const;
    unsigned long getNumNodes() const;
    double getEdgeWeight(unsigned long nOrigIndex, unsigned long nDestIndex);

    bool addNode(const T &in);
    bool removeNode(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w, EdgeType type);
    bool removeEdge(const T &sourc, const T &dest);

    bool relax(Node<T> *source, Node<T> *way, double weight);
    void dijkstra(const T &sourceInfo);
    void floydWarshall();

    bool isDAG() const;
    bool dfsIsDAG(Node<T> *n) const;

    std::vector<T> bellmanFordSearch(const T &source) const;
};

/*
 * Auxiliary function to find a Node with a given content.
 */
template <class T>
Node<T> * Graph<T>::getNode(const T &in) const {
    for (auto node : nodeSet){
        if (node->getInfo() == in){
            return node;
        }
    }

    return nullptr;
}

template <class T>
unsigned long Graph<T>::getNumNodes() const {
    return nodeSet.size();
}

template<class T>
double Graph<T>::getEdgeWeight(unsigned long nOrigIndex, unsigned long nDestIndex) {
    if(nOrigIndex == nDestIndex){
        return 0;
    }

    for(auto e: nodeSet[nOrigIndex]->edges){
        if(e.dest == nodeSet[nDestIndex]){
            return e.weight;
        }
    }

    return std::numeric_limits<double>::max();
}

/*
 *  Adds a Node with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a Node with that content already exists.
 */
template <class T>
bool Graph<T>::addNode(const T &in) {
    if(getNode(in) != nullptr){
        return false;
    }

    nodeSet.push_back(new Node<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination Node does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, EdgeType type) {
    auto v1 = getNode(sourc);
    auto v2 = getNode(dest);

    if (v1 == nullptr || v2 == nullptr)
        return false;

    if(type == EdgeType::twoWay){
        v1->addEdge(v2,w);
        v2->addEdge(v1,w);
        return true;
    }
    else if(type == EdgeType::oneWay){
        v1->addEdge(v2,w);
        return true;
    }

    return false;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = getNode(sourc);
    auto v2 = getNode(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 *  Removes a Node with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such Node does not exist.
 */
template <class T>
bool Graph<T>::removeNode(const T &in) {
    for (auto it = nodeSet.begin(); it != nodeSet.end(); it++){
        if ((*it)->info  == in) {
            auto v = *it;
            nodeSet.erase(it);
            for (auto u : nodeSet){
                u->removeEdgeTo(v);
            }
            delete v;
            return true;
        }
    }
    return false;
}

template<class T>
bool Graph<T>::relax(Node<T> *source, Node<T> *way, double weight) {
    if(source->dist + weight < way->dist){
        way->dist = source->dist + weight;
        way->path = source;

        return true;
    }
    return false;
}

template<class T>
void Graph<T>::dijkstra(const T &sourceInfo){
    for(auto n: nodeSet){
        n->dist = std::numeric_limits<double>::max();
        n->path = nullptr;
    }

    Node<T> *source = getNode(sourceInfo);
    if(source == nullptr){
        return;
    }
    source->dist = 0;

    MutablePriorityQueue<Node<T>> queue;
    queue.insert(source);

    while(!queue.empty()){
        Node<T> *min = queue.extractMin();
        for(auto e: min->edges){
            auto oldDist = e.dest->dist;

            if(relax(min, e.dest, e.weight)){
                if(oldDist == std::numeric_limits<double>::max()){
                    queue.insert(e.dest);
                }
                else{
                    queue.decreaseKey(e.dest);
                }
            }
        }
    }
}

template<class T>
void Graph<T>::floydWarshall() {
    W = new double *[nodeSet.size()];
    P = new int *[nodeSet.size()];
    for(unsigned int i=0; i < nodeSet.size(); i++){
        W[i] = new double[nodeSet.size()];
        P[i] = new int[nodeSet.size()];
        for(unsigned int j=0; j < nodeSet.size(); j++){
            W[i][j] = 0;
            P[i][j] = nullptr;
        }
    }
}

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto n : nodeSet) {
        n->visited = false;
        n->processing = false;
    }
    for (auto n : nodeSet)
        if (! n->visited)
            if (!dfsIsDAG(n) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Node<T> *n) const {
    n->visited = true;
    n->processing = true;
    for (auto & e : n->edges) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (!dfsIsDAG(w))
                return false;
    }
    n->processing = false;
    return true;
}

template <class T>
std::vector<T> Graph<T>::bellmanFordSearch(const T & source) const {
    // TODO (22 lines)
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    std::vector<T> res;
    return res;
}

#endif /* GRAPH_H_ */