//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_EDGE_H
#define CAL_T4GA4_EDGE_H

template <class T>
class Edge {
private:
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};


#endif //CAL_T4GA4_EDGE_H
