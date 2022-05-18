#include <stdlib.h>
#include "BoundedPriorityQueue.h"

typedef struct node_t
{
  double key;
  size_t value;
  struct node_t *prev;
  struct node_t *next;
} Node;

struct bounded_priority_queue_t
{
  Node *first;
  Node *last;
  size_t capacity;
  size_t size;
};

BoundedPriorityQueue *bpqCreate(size_t capacity)
{
  BoundedPriorityQueue *bpq = malloc(sizeof(BoundedPriorityQueue));
  bpq->first = NULL;
  bpq->last = NULL;
  bpq->capacity = capacity;
  bpq->size = 0;
  return bpq;
}

void bpqFree(BoundedPriorityQueue *bpq)
{
  Node *n = bpq->first, *next = NULL;
  while (n)
  {
    next = n->next;
    free(n);
    n = next;
  }
  free(bpq);
}

bool bpqInsert(BoundedPriorityQueue *bpq, double key, size_t value)
{
  if (bpq->size == bpq->capacity) // bqp est plein
    return false;

  Node *n = bpq->first, *prev = NULL, *new;
  new = malloc(sizeof(Node));
  new->key = key;
  new->value = value;
  new->prev = NULL;
  new->next = NULL;

  if (!new) // Echec malloc
    return false;

  while (n) // On cherche un noeud ayant une clé de plus grande valeur
  {
    if (n->key > key)
      break;
    prev = n;
    n = n->next;
  }
  if (prev) // On s'accroche au précédent
    prev->next = new;
  else // Sinon on est en tête
    bpq->first = new;
  if (n) // On a remplacé un noeud
  {
    new->next = n;
    n->prev = new;
  }
  else // Sinon on est à la fin
    bpq->last = new;
  bpq->size++;
  return true;
}

void bpqReplaceMaximum(BoundedPriorityQueue *bpq, double key, size_t value)
{
  Node *n = bpq->last;
  bpq->last->prev = NULL;
  free(n);
  bpq->size--;
  bpqInsert(bpq, key, value);
}

double bpqMaximumKey(const BoundedPriorityQueue *bpq)
{
  return bpq->last->value;
}

size_t *bpqGetItems(const BoundedPriorityQueue *bpq)
{
  size_t *array = calloc(bpq->size, sizeof(size_t));
  Node *n = bpq->first;
  for (size_t i = 0; i < bpq->size; i++)
  {
    array[i] = n->value;
    n = n->next;
  }
  return array;
}

size_t bpqSize(const BoundedPriorityQueue *bpq)
{
  return bpq->size;
}

size_t bpqCapacity(const BoundedPriorityQueue *bpq)
{
  return bpq->capacity;
}
