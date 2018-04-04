#ifndef _GARBAGEMANAGEMENT_H_
#define _GARBAGEMANAGEMENT_H_

#include "Graph.h"

class GarbageManagement{
private:
    Graph graph;

    std::vector<Container> containers;
//    std::vector<Station> stations;
//    std::vector<Garage> garages;
public:
    GarbageManagement();
    Graph getGraph();
    std::vector<Container> getContainers();

    void addContainer(Container container);

    virtual ~GarbageManagement();

  bool load();
};

#endif
