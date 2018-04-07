#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include "Edge.h"

template <class T> class Graph; //foward declaration

template <class T>
class Node {
    T info;                // contents
    std::vector<Edge<T>> edges;  // list of outgoing edges

    double dist = 0;        // auxiliary field used by dijkstra
    Node<T> *path = nullptr; // auxiliary field used by dijkstra

    bool visited;          // auxiliary field used by dfs and bfs
    int indegree;          // auxiliary field used by topsort
    bool processing;       // auxiliary field used by isDAG

public:
    Node(T in);

    T getInfo() const;
    void addEdge(Node<T> *dest, double w);
    bool removeEdgeTo(Node<T> *d);

    friend class Graph<T>; //make Graph class a friend so that it can access private and protected fields
};

template <class T>
Node<T>::Node(T in): info(in) {}

template <class T>
T Node<T>::getInfo() const{
    return this->info;
}

/*
 * Auxiliary function to add an outgoing edge to a Node (this),
 * with a given destination Node (dest) and edge weight (w).
 */
template <class T>
void Node<T>::addEdge(Node<T> *dest, double w) {
    this->edges.push_back(Edge<T>(dest, w));
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a Node (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Node<T>::removeEdgeTo(Node<T> *d) {
    for (auto it = edges.begin(); it != edges.end(); it++){
        if (it->dest  == d) {
            edges.erase(it);
            return true;
        }
    }
    return false;
}

#endif //_NODE_H
