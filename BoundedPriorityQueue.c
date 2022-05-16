#include "BoundedPriorityQueue.h"

struct bounded_priority_queue_t {
  // A completer
};

BoundedPriorityQueue* bpqCreate(size_t capacity) {
  // A completer
}

void bpqFree(BoundedPriorityQueue* bpq) {
  // A completer
}

bool bpqInsert(BoundedPriorityQueue* bpq, double key, size_t value) {
  // A completer
}

void bpqReplaceMaximum(BoundedPriorityQueue* bpq, double key, size_t value) {
  // A completer
}

double bpqMaximumKey(const BoundedPriorityQueue* bpq) {
  // A completer
} 

size_t* bpqGetItems(const BoundedPriorityQueue* bpq) {
  // A completer
}

size_t bpqSize(const BoundedPriorityQueue* bpq) {
  // A completer
}

size_t bpqCapacity(const BoundedPriorityQueue* bpq) {
  // A completer
}
