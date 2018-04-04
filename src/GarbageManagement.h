#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include "Graph.h"

class GarbageManagement{
private:
    Graph graph;

public:
    GarbageManagement();

    virtual ~GarbageManagement();

  bool load();
};

#endif
