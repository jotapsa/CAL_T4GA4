#ifndef _INPUTPARSER_H
#define _INPUTPARSER_H

#include "Graph.h"
#include "GarbageManagement.h"

#define NODES_FILEPATH "../resources/nodes.txt"
#define EDGES_FILEPATH "../resources/edges.txt"
#define EDGES_INFO_FILEPATH "../resources/edges_info.txt"

//TODO: make load functions void & exit if shit hits the fan.

bool loadNodes(GarbageManagement &management);
bool loadEdges(GarbageManagement &management);
bool loadEdgesInfo(GarbageManagement &management);

//TODO: save functions.
void saveNodes(const GarbageManagement &management);
void saveEdges(const GarbageManagement &management);
void saveEdgesInfo(const GarbageManagement &management);




#endif //_INPUTPARSER_H
