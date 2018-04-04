#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include "Graph.h"
#include "GraphViewer.h"

class GarbageManagement{
private:
  GraphViewer *viewer;
  Graph graph;

public:
  GarbageManagement();

  virtual ~GarbageManagement();

  void loadNodes();
};

#endif
