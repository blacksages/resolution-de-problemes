#include "NearestNeighbours.h"
#include "BoundedPriorityQueue.h"
#include "DynamicTimeWarping.h"
#include <stdlib.h>
#include <math.h>

SketchDistance* nearestNeighbours(const Dataset* dataset, Sketch query, size_t k) {
  BoundedPriorityQueue *bpq = bpqCreate(k);
  SketchDistance *sketch_distances =  calloc(k, sizeof(SketchDistance));
  double dist = +INFINITY;
  for(size_t i = 0; i < dataset->size; i++)
  {
    if(bpqSize(bpq) == bpqCapacity(bpq))
      dist = dtw(query, dataset->sketches[i], bpqMaximumKey(bpq));
    else
      dist = dtw(query, dataset->sketches[i], +INFINITY);
    if (dist < bpqMaximumKey(bpq))
      if(!bpqInsert(bpq, dist, i))
        bpqReplaceMaximum(bpq, dist, i);
  }
  size_t *values = bpqGetItems(bpq);
  for (size_t i = 0; i < bpqSize(bpq); i++)
  {
      (sketch_distances + i)->sketch = dataset->sketches + values[i];
      (sketch_distances + i)->distance = dtw(query, dataset->sketches[values[i]], +INFINITY);
  }

  return sketch_distances;
}
