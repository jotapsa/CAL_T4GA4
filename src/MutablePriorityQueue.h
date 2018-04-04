//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#define CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#include <vector>
#include "Vertex.h"

class Vertex;

class MutablePriorityQueue {
  std::vector<Vertex *> H;
  void heapifyUp(unsigned i);
  void heapifyDown(unsigned i);
  inline void set(unsigned i, Vertex * x);
public:
  MutablePriorityQueue();
  void insert(Vertex * x);
  Vertex * extractMin();
  void decreaseKey(Vertex * x);
  bool empty();
  bool elementExists(Vertex *x);
};

#endif //CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
