#include "GarbageManagement.h"
#include "NodeParser.h"

GarbageManagement::GarbageManagement() {
  this->viewer = new GraphViewer(600, 600, false);
  this->viewer->createWindow(600, 600);
  this->viewer->defineVertexColor("blue");
  this->viewer->defineEdgeColor("black");
}

GarbageManagement::~GarbageManagement() {
    // TODO Auto-generated destructor stub
}

void GarbageManagement::loadNodes(){

}
