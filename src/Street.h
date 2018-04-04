#ifndef _STREET_H
#define _STREET_H

#include <string>
#include "Node.h"
#include "Aux.h"

class Street {
private:
  unsigned long int ID;
  std::string roadName;
  int edgeType;
  Node *n1;
  Node *n2;
public:
  Street(unsigned long int ID, std::string name, int edgeType);
  Street(unsigned long int ID, Node &n1, Node &n2);

  unsigned long int getID();
  std::string getName();
  int getEdgeType();

  void setName(std::string name);
  void setEdgeType(EdgeType type);
  void addNodes(Node &n1, Node &n2);
  Node* getFirstNode(){return this->n1;}
  Node* getSecondNode(){return this->n2;}
};


#endif //_STREET_H
