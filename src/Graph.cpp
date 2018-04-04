//
// Created by dnc on 01-04-2018.
//

#include "Graph.h"


Graph::Graph() {

  vertexSet = std::vector<Node*>();
}

int Graph::getNumVertex() const {
  return vertexSet.size();
}

std::vector<Node *> Graph::getVertexSet() const {
  return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Node * Graph::findVertex(const unsigned long &in) const {

  for(auto v : vertexSet) {
    if (v->id == in)
      return v;
  }

  return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const unsigned long &in, Location &coord) {

  if(findVertex(in) != NULL)
    return false;

  vertexSet.push_back(new Node(in, coord));

  return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const unsigned long &sourc, const unsigned long &dest, double w) {
  auto v1 = findVertex(sourc);
  auto v2 = findVertex(dest);
  if (v1 == NULL || v2 == NULL)
    return false;
  v1->addEdge(v2,w);
  return true;
}


/**************** Single Source Shortest Path algorithms ************/

bool Graph::relax(Node * vertex, Node *w, double weight) {

  if(vertex->dist + weight < w->dist) {
    w->dist = vertex->dist + weight;

    w->setPath(vertex);

    return true;
  }
  else
    return false;
}

void Graph::dijkstraShortestPath(const unsigned long &origin)
{
  Node  *source = findVertex(origin);

  Node *min;

  if(source == NULL)
    return;

  for(auto v: vertexSet) {
    v->dist = std::numeric_limits<double>::max();
    v->path = NULL;
  }

  MutablePriorityQueue q;

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

std::vector<unsigned long> Graph::getPath(const unsigned long &origin, const unsigned long &dest){

  std::vector<unsigned long> res;

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

void Graph::unweightedShortestPath(const unsigned long &orig) {

  for(auto v : vertexSet){
    v->dist = INF;
    v->path = nullptr;
  }

  auto s = findVertex(orig);

  if(s == nullptr)
    return;

  MutablePriorityQueue q;

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

void Graph::bellmanFordShortestPath(const unsigned long &orig) {

  Node *source = findVertex(orig);

  if(source == NULL)
    return;

  for(auto v: vertexSet){
    v->dist = INF;
    v->path = NULL;
  }

  MutablePriorityQueue q;

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


void Graph::floydWarshallShortestPath() {
  // TODO
}


std::vector<unsigned long> Graph::getfloydWarshallPath(const unsigned long &orig, const unsigned long &dest) const{
  std::vector<unsigned long> res;
  // TODO
  return res;
}

void Graph::printNodes() {

  for(auto v: vertexSet) {
     v->print();
  }
}

