//#ifndef _NODE_H
//#define _NODE_H
//
//#include <string>
//#include <vector>
//#include "Edge.h"
//
//class Node {
//private:
//  unsigned long ID;                       // Node Id
//  std::pair<double, double> coordinates;
//  std::vector<Edge> edges;  // outgoing edges
//
//public:
//  Node(unsigned long ID, std::pair<double, double> coordinates);
//
//  unsigned long getID() const;
//  std::pair<double, double> getCoordinates();
//
//  void addEdge(Node *n, double w);
//};
//
//#endif //_NODE_H

#ifndef _NODE_H
#define _NODE_H

#include <vector>
#import "Edge.h"

template <class T>
class Node {
    T info;                // contents
    std::vector<Edge<T> > edges;  // list of outgoing edges
    bool visited;          // auxiliary field used by dfs and bfs
    int indegree;          // auxiliary field used by topsort
    bool processing;       // auxiliary field used by isDAG

    bool removeEdgeTo(Node<T> *d);
public:
    Node(T in);

    T getInfo() const;
    void addEdge(Node<T> *dest, double w);
};

template <class T>
Node<T>::Node(T in): info(in) {}

template <class T>
void Node<T>::getInfo() const{
    return this->info;
}

/*
 * Auxiliary function to add an outgoing edge to a Node (this),
 * with a given destination Node (d) and edge weight (w).
 */
template <class T>
void Node<T>::addEdge(Node<T> *d, double w) {
    // TODO (1 line)
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a Node (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Node<T>::removeEdgeTo(Node<T> *d) {
    // TODO (6 lines)
    // HINT: use an iterator to scan the "adj" vector and then erase the edge.
    return false;
}


#endif //_NODE_H
