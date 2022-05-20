#include "NearestNeighbours.h"
#include "BoundedPriorityQueue.h"
#include "DynamicTimeWarping.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

SketchDistance* nearestNeighbours(const Dataset* dataset, Sketch query, size_t k) {
  // Liste pour stocker les plus proches voisins
  BoundedPriorityQueue *bpq = bpqCreate(k);
  if (bpq == NULL) // Echec create
    return NULL;
  // Les distances à retourner
  SketchDistance *sketch_distances =  calloc(k, sizeof(SketchDistance));
  if (sketch_distances == NULL) // Echec calloc
  {
    bpqFree(bpq);
    return NULL;
  }
  double dist = +INFINITY;

  for(size_t i = 0; i < dataset->size; i++)
  {
    if(bpqSize(bpq) == bpqCapacity(bpq)) // On a déjà une file remplie
      dist = dtw(query, dataset->sketches[i], bpqMaximumKey(bpq));
    else // Sinon on a pas de distance max
      dist = dtw(query, dataset->sketches[i], +INFINITY);
    if(!bpqInsert(bpq, dist, i)) // On essaye d'insérer
      if (dist < bpqMaximumKey(bpq)) // Sinon on ajoute la distance si elle est au moins meilleure que le pire voisin
        bpqReplaceMaximum(bpq, dist, i);
  }
  size_t *values = bpqGetItems(bpq); // Les indices des plus proches voisins
  if (values == NULL)
  {
    free(sketch_distances);
    bpqFree(bpq);
    return NULL;
  }
  for (size_t i = 0; i < bpqSize(bpq); i++) // Distances à retourner
  {
      (sketch_distances + i)->sketch = dataset->sketches + values[i];
      (sketch_distances + i)->distance = dtw(query, (dataset->sketches)[values[i]], +INFINITY);
  }
  free(values);
  bpqFree(bpq);
  return sketch_distances;
}
