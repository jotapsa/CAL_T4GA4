#ifndef _STREET_H
#define _STREET_H

#include <string>
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


#endif //_STREET_H
