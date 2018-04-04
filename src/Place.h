#ifndef _PLACE_H_
#define _PLACE_H_

#include "Node.h"

//TODO: make this class abstract (how ?) (see virtual pure functions)

class Place{
protected:
  Node *node;
public:
  explicit Place(Node &node);
};

#endif /* _PLACE_H_ */
