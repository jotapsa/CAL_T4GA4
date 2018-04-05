//#ifndef GRAPH_H_
//#define GRAPH_H_
//
//#include <vector>
//#include "Street.h"
//#include "Container.h"
//#include "Node.h"
//#include "Place.h"
//
//class Graph {
//private:
//    std::vector<Node *> nodeSet;    // Node set
//
//    std::vector<Street *> streets;
//    std::vector<Place *> containers;
//public:
//    Graph();
//    int getNumNodes() const;
//
//    std::vector<Node*> getnodeSet() const;
//    std::vector<Street *> getStreets(){return this->streets;}
//    std::vector<Place *> getContainers(){return this->containers;}
//
//    Node *getNode(const unsigned long &id) const;
//
//    bool addNode(Node *node);
//
//    bool addEdge(const unsigned long &sourc, const unsigned long &dest, double w, EdgeType type);
//};
//
//#endif /* GRAPH_H_ */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Aux.h"
#include <vector>
#include <queue>

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Graph {
private:
    std::vector<Node<T> *> nodeSet;    // Node set

    void depthFirstSearchVisit(Node<T> *v,  std::vector<T> & res) const;
    bool depthFirstSearchIsDAG(Node<T> *v) const;
public:
    Node<T> * getNode(const T &in) const;
    unsigned long getNumNodes() const;
    bool addNode(const T &in);
    bool removeNode(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, EdgeType type);
    bool removeEdge(const T &sourc, const T &dest);
    std::vector<T> depthFirstSearch() const;
    std::vector<T> bellmanFordSearch(const T &source) const;
    std::vector<T> topsort() const;
    int maxNewChildren(const T &source, T &inf) const;
    bool isDAG() const;
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

    if(type == twoWay){
        v1->addEdge(v2,w);
        v2->addEdge(v1,w);
        return true;
    }
    else if(type == oneWay){
        v1->addEdge(v2,w);
        return true;
    }

    return false;
}

/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    // TODO (5 lines)
    // HINT: Use "getNode" to obtain the actual vertices.
    // HINT: Use the next function to actually remove the edge.
    return false;
}

/****************** 1d) removeNode ********************/

/*
 *  Removes a Node with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such Node does not exist.
 */
template <class T>
bool Graph<T>::removeNode(const T &in) {
    // TODO (10 lines)
    // HINT: use an iterator to scan the "nodeSet" vector and then erase the Node.
    // HINT: take advantage of "removeEdgeTo" to remove incoming edges.
    return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::depthFirstSearch() const {
    // TODO (7 lines)
    std::vector<T> res;
    return res;
}

/*
 * Auxiliary function that visits a Node (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::depthFirstSearchVisit(Node<T> *v, std::vector<T> & res) const {
    // TODO (7 lines)
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the Node with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
std::vector<T> Graph<T>::bellmanFordSearch(const T & source) const {
    // TODO (22 lines)
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    std::vector<T> res;
    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    // TODO (26 lines)
    std::vector<T> res;
    return res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the Node with the given source contents (source).
 * During the search, determines the Node that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that Node (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    // TODO (28 lines, mostly reused)
    return 0;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a Node
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    // TODO (9 lines, mostly reused)
    // HINT: use the auxiliary field "processing" to mark the vertices in the stack.
    return true;
}

/**
 * Auxiliary function that visits a Node (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a Node in the stack is found.
 */
template <class T>
bool Graph<T>::depthFirstSearchIsDAG(Node<T> *v) const {
    // TODO (12 lines, mostly reused)
    return true;
}

#endif /* GRAPH_H_ */