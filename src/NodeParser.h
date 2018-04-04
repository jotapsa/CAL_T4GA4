#ifndef CAL_T4GA4_NODEPARSER_H
#define CAL_T4GA4_NODEPARSER_H

#include <mach/boolean.h>
#include "Graph.h"

#define NODES_FILEPATH "../resources/nodes.txt"
#define EDGES_INFO_FILEPATH "../resources/edges_info.txt"
#define EDGES_FILEPATH "../resources/edges.txt"

class NodeParser {
public:
    bool loadNodes(Graph &graph);
    bool loadEdges(Graph &graph);
    bool loadEdgesInfo(Graph &graph);
};


#endif //CAL_T4GA4_NODEPARSER_H
