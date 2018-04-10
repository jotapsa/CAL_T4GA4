#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "MutablePriorityQueue.h"
#include "EdgeType.h"
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

template <class T> class Edge;
template <class T> class Graph;

//TODO: A*
//TODO: Path finding optimizations.
//TODO: improve heuristic

template <class T>
class Graph {
    private:
    std::vector<Node<T> *> nodeSet;    // Node set

    double ** W;   //minimum weight matrix
    Node<T> *** P;   //shortest path matrix

    public:
    Node<T> * getNode(const T &in) const;
    std::vector<Node<T> *> getNodeSet() const;
    unsigned long getNumNodes() const;
    double getEdgeWeight(unsigned long nOrigIndex, unsigned long nDestIndex);

    bool addNode(const T &in);
    bool removeNode(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w, EdgeType type = EdgeType::oneWay);
    bool removeEdge(const T &sourc, const T &dest);

    void invertEdges();
    void resetNodeAuxFields();

    bool relax(Node<T> *source, Node<T> *way, double weight);
    void dijkstra(const T &sourceInfo);
    T* getNodeWithShortestPathDijkstra(const std::vector<T> &nodes);
    std::vector<T> getDijkstraPath(const T &dest);
    double dijkstraHeuristic(const T &dest);

    void floydWarshall();
    T* getNodeWithShortestPathFloydWarshall(const T &origin, std::vector<T> &nodes);
    void getfloydWarshallPath(std::vector<T> &path, const T &origin, const T &dest);
    void floydWarshallHeuristic(double &cost, const T &origin, const T &dest);

    std::vector<T> dfs() const;
    void dfsVisit(Node<T> *n, std::vector<T> &res) const;

    bool isDAG() const;
    bool dfsIsDAG(Node<T> *n) const;

    std::vector<T> topsort() const;

    Graph<T> clone();
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

template<class T>
std::vector<Node<T> *> Graph<T>::getNodeSet() const {
    return this->nodeSet;
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
void Graph<T>::resetNodeAuxFields() {
    for(auto n:nodeSet){
        n->resetAuxFields();
    }
}


template<class T>
void Graph<T>::invertEdges() {
    for(auto n: nodeSet){
        for(auto e: n->edges){
            removeEdge(n->info, e.dest->info);
            addEdge(e.dest->info, n->info, e.weight);
        }
    }
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
T* Graph<T>::getNodeWithShortestPathDijkstra(const std::vector<T> &nodes) {
    double min = std::numeric_limits<double>::max();
    double cost;
    typename std::vector<T>::iterator bestOption = nodes.begin();

    for(typename std::vector<T>::iterator it = nodes.begin(); it!= nodes.end(); ++it){
        cost = dijkstraHeuristic(it);
        if(cost < min){
            min = cost;
            bestOption = it;
        }
    }

    return &bestOption;
}

template<class T>
std::vector<T> Graph<T>::getDijkstraPath(const T &dest) {
    std::vector<T> path;
    auto n = getNode(dest);
    if(n == nullptr || n->dist == std::numeric_limits<double>::max()){
        return path;
    }
    for(; n!= nullptr; n = n->path){
        path.push_back(n->info);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template<class T>
double Graph<T>::dijkstraHeuristic(const T &dest) {
    double cost = 0;
    auto n = getNode(dest);
    if(n == nullptr || n->dist == std::numeric_limits<double>::max()){
        return cost;
    }
    for(; n!= nullptr; n = n->path){
        cost += n->dist;
    }
    return cost;
}

/**
* from http://algoritmy.net/article/45708/Floyd-Warshall-algorithm
* Floyd-Warshall algorithm. Finds all shortest paths among all pairs of nodes
* @param d matrix of distances (std::numeric_limits<double>::max() represents positive infinity)
* stores matrix of predecessors
*/
template<class T>
void Graph<T>::floydWarshall() {
    //initialize.
    W = new double *[nodeSet.size()];
    P = new Node<T> **[nodeSet.size()];
    for(unsigned long i=0; i < nodeSet.size(); i++){
        W[i] = new double[nodeSet.size()];
        P[i] = new Node<T> *[nodeSet.size()];
        for(unsigned long j=0; j < nodeSet.size(); j++){
            W[i][j] = getEdgeWeight(i, j);
            if(W[i][j] != 0 && W[i][j] != std::numeric_limits<double>::max()){
                P[i][j] = nodeSet.at(i);
            }else{
                P[i][j] = nullptr;
            }
        }
    }

    for(unsigned long k=0; k < nodeSet.size(); k++){
        for(unsigned long i=0; i < nodeSet.size(); i++){
            for(unsigned long j=0; j < nodeSet.size(); j++){
                if(W[i][k] == std::numeric_limits<double>::max() || W[k][j] == std::numeric_limits<double>::max()){
                    continue;
                }

                if(W[i][j] > W[i][k] + W[k][j]){
                    W[i][j] = W[i][k] + W[i][k];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

template<class T>
void Graph<T>::getfloydWarshallPath(std::vector<T> &path, const T &origin, const T &dest) {
    unsigned long nDestIndex = nodeSet.size();
    unsigned long nOriginIndex = nodeSet.size();

    for(unsigned long i=0; i < nodeSet.size(); i++){
        if(nodeSet[i]->info == origin){
            nOriginIndex = i;
        }
        if(nodeSet[i]->info == dest){
            nDestIndex = i;
        }

        //maybe we already found the indexes
        if(nOriginIndex != nodeSet.size() && nDestIndex != nodeSet.size()){
            break;
        }
    }

    if(origin == dest){
        path.push_back(origin);
    }else if(P[nOriginIndex][nDestIndex] != nullptr){
        getfloydWarshallPath(path, origin, P[nOriginIndex][nDestIndex]->getInfo());
        path.push_back(dest);
    }
}

template<class T>
void Graph<T>::floydWarshallHeuristic(double &cost, const T &origin, const T &dest) {
    unsigned long nDestIndex = nodeSet.size();
    unsigned long nOriginIndex = nodeSet.size();

    for(unsigned long i=0; i < nodeSet.size(); i++){
        if(nodeSet[i]->info == origin){
            nOriginIndex = i;
        }
        if(nodeSet[i]->info == dest){
            nDestIndex = i;
        }

        //maybe we already found the indexes
        if(nOriginIndex != nodeSet.size() && nDestIndex != nodeSet.size()){
            break;
        }
    }

    if(origin == dest){
        //all good
    }else if(P[nOriginIndex][nDestIndex] != nullptr){
        floydWarshallHeuristic(cost, origin, P[nOriginIndex][nDestIndex]->getInfo());
        cost+=W[nOriginIndex][nDestIndex];
    }
}

template<class T>
T* Graph<T>::getNodeWithShortestPathFloydWarshall(const T &origin, std::vector<T> &nodes) {
    double min = std::numeric_limits<double>::max();
    double cost = 0;
    typename std::vector<T>::iterator bestOption = nodes.begin();

    for(typename std::vector<T>::iterator it = nodes.begin(); it!= nodes.end(); ++it){
        floydWarshallHeuristic(cost, origin, it);
        if(cost < min){
            min = cost;
            bestOption = it;
        }
    }

    return &bestOption;
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    //initialize every node as not visited
    for (auto n : nodeSet){
        n->visited = false;
    }

    for (auto n : nodeSet){
        if (!n->visited){
            dfsVisit(n, res);
        }
    }

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

template<class T>
void Graph<T>::dfsVisit(Node<T> *n, std::vector<T> &res) const {
    n->visited = true;
    res.push_back(n->info);

    for (auto & e: n->edges) {
        auto w = e.dest;
        if ( ! w->visited){
            dfsVisit(w, res);
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
    for (auto n : nodeSet){
        if (! n->visited)
            if (!dfsIsDAG(n) )
                return false;
    }
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

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
std::vector<T> Graph<T>::topsort() const {
    std::vector<T> res;

    for (auto v : nodeSet)
        v->indegree = 0;
    for (auto v : nodeSet)
        for (auto & e : v->adj)
            e.dest->indegree++;

    std::queue<Node<T>*> q;
    for (auto v : nodeSet)
        if (v->indegree == 0)
            q.push(v);

    while( !q.empty() ) {
        Node<T>* v = q.front();
        q.pop();
        res.push_back(v->info);
        for(auto & e : v->edges) {
            auto w = e.dest;
            w->indegree--;
            if(w->indegree == 0)
                q.push(w);
        }
    }

    if ( res.size() != nodeSet.size() ) {
        res.clear();
        return res;
    }

    return res;
}

template<class T>
Graph<T> Graph<T>::clone() {
    Graph<T> clone;
    for(auto n: nodeSet){
        clone.addNode(n->info);
        for(auto e: n->edges){
            clone.addEdge(n->info, e.dest->getInfo(), e.weight);
        }
    }

    return clone;
}

#endif /* GRAPH_H_ */