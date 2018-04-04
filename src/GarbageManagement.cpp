#include "GarbageManagement.h"
#include <iostream>
#include "NodeParser.h"

using namespace std;

GarbageManagement::GarbageManagement() {
    if(!load()){
        return;
    };
}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}

bool GarbageManagement::load(){
    if(!loadNodes(this->graph)){
        cout << "Failed to read nodes!" << endl;
        return false;
    };

    std::cout << this->graph.getNumNodes() << " nodes were successfully read!\n";

//    std::cout << this->graph.getContainers().size() << " containers!\n";

    if(!loadEdges(this->graph)){
        cout << "Failed to read edges!" << endl;
        return false;
    };

    std::cout << this->graph.getStreets().size() << " edges were successfully read!\n";

    if(!loadEdgesInfo(this->graph)){
        cout << "Failed to read edges info!" << endl;
        return false;
    };

    std::cout << this->graph.getStreets().size() << " edges were successfully updated!\n";

    return true;
}
