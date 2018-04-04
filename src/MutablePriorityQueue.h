//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#define CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#include <vector>
#include "Node.h"

class Node;

class MutablePriorityQueue {
  std::vector<Node *> H;
  void heapifyUp(unsigned i);
  void heapifyDown(unsigned i);
  inline void set(unsigned i, Node * x);
public:
  MutablePriorityQueue();
  void insert(Node * x);
  Node * extractMin();
  void decreaseKey(Node * x);
  bool empty();
  bool elementExists(Node *x);
};

#endif //CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
