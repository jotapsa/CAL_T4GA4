//
// Created by dnc on 31-03-2018.
//

#include "MutablePriorityQueue.h"
// Index calculations
#define parent(i) ((i) >> 1)
#define leftChild(i) ((i) << 1)

MutablePriorityQueue::MutablePriorityQueue() {
  H.push_back(NULL);
  // indices will be used starting in 1
  // to facilitate parent/child calculations
}

bool MutablePriorityQueue::empty() {
  return H.size() == 1;
}

Vertex* MutablePriorityQueue::extractMin() {
  auto x = H[1];
  x->queueIndex = 0;
  H[1] = H.back();
  H.pop_back();
  if ( ! empty())
    heapifyDown(1);
  return x;
}


void MutablePriorityQueue::insert(Vertex *x) {
  H.push_back(x);
  heapifyUp(H.size()-1);
}


void MutablePriorityQueue::heapifyUp(unsigned i) {
  auto x = H[i];
  while (i > 1 && *x < *H[parent(i)]) {
    set(i, H[parent(i)]);
    i = parent(i);
  }
  set(i, x);
}


void MutablePriorityQueue::decreaseKey(Vertex *x) {
  heapifyUp(x->queueIndex);
}


void MutablePriorityQueue::heapifyDown(unsigned i) {
  auto x = H[i];
  while (true) {
    unsigned k = leftChild(i);
    if (k >= H.size())
      break;
    if (k+1 < H.size()  && *H[k+1] < *H[k])
      k++; // right child of i
    if ( ! (*H[k] < *x) )
      break;
    set(i, H[k]);
    i = k;
  }
  set(i, x);
}


void MutablePriorityQueue::set(unsigned i, Vertex * x) {
  H[i] = x;
  x->queueIndex = i;
}


bool MutablePriorityQueue::elementExists(Vertex *x){

  for(auto v: H)
  {
    if(v->id == x->id)
      return true;
  }

  return false;
}