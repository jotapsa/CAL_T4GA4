//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_VERTEX_H
#define CAL_T4GA4_VERTEX_H

template <class T>
class Vertex {

private:
    T info;                // contents
    vector<Edge<T> > adj;  // outgoing edges
    bool visited;          // auxiliary field
    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    bool processing = false;
    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


#endif //CAL_T4GA4_VERTEX_H
