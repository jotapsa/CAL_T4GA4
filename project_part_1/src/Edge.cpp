//
// Created by dnc on 31-03-2018.
//

#include "Edge.h"

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w) {
    dest = d;
    weight = w;
}