//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_VERTEX_H
#define CAL_T4GA4_VERTEX_H

#include "Location.h"
#include "MutablePriorityQueue.h"
#include "Edge.h"

class Edge;
class Location;

class Vertex {
  unsigned long id;                       // vertex Id
  Location coordinates = Location(0, 0, 0, 0);       // vertex coordinates
  std::vector<Edge> adj;  // outgoing edges
  bool visited;               // auxiliary field
  double dist = 0;            //algorithm distance
  double geoDist = 0;         //geo distance to source vertex for A*
  Vertex *path = NULL;
  int queueIndex = 0; 		    // required by MutablePriorityQueue
  bool processing = false;
  void addEdge(Vertex *dest, double w);

public:
  Vertex(unsigned long in, Location *l, Location coordinates);
  bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
  unsigned long getId() const;
  double getDist() const;
  Vertex *getPath() const;
  Location  getLocation() const;
  friend class Graph;
  friend class MutablePriorityQueue<Vertex>;
  friend class Edge;
};


#endif //CAL_T4GA4_VERTEX_H
