//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#define CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
#include <vector>


template <class T>
class MutablePriorityQueue {
  std::vector<T *> H;
  void heapifyUp(unsigned i);
  void heapifyDown(unsigned i);
  inline void set(unsigned i, T * x);
public:
  MutablePriorityQueue();
  void insert(T * x);
  T * extractMin();
  void decreaseKey(T * x);
  bool empty();
  bool elementExists(T *x);
};

#endif //CAL_T4GA4_MUTABLEPRIORITYQUEUE_H
