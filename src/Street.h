#ifndef CAL_T4GA4_STREET_H
#define CAL_T4GA4_STREET_H

#include <string>
#include "Location.h"
#include "Node.h"

class Street {
private:
  unsigned long id;
  std::string roadName;
  int edgeType;
  Node * n1;
  Node * n2;
public:
  Street(unsigned long id, std::string name, int edgeType);
  unsigned long getId();
  std::string getName();
  int getEdgeType();
  void addNodes(Node *n1, Node *n2);
  Node* getFirstNode(){return this->n1;}
  Node* getSecondNode(){return this->n2;}
};


#endif //CAL_T4GA4_STREET_H
