#ifndef _EDGE_H
#define _EDGE_H

template <class T> class Node;
template <class T> class Graph; //foward declaration

template <class T>
class Edge {
    Node<T> * dest;      // destination node
    double weight;       // edge weight
public:
    Edge(Node<T> *d, double w);

    friend class Graph<T>;
};

template <class T>
Edge<T>::Edge(Node<T> *d, double w): dest(d), weight(w) {}

#endif
