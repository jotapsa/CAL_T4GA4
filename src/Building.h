#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Building.h"
#include "Node.h"

//TODO: make this class abstract (how ?) (see virtual pure functions)

class Building{
protected:
  Node *node;
public:
  explicit Building(Node &node);
};

#endif /* _BUILDING_H_ */
